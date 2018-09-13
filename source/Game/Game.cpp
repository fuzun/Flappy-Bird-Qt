/*
MIT License
Copyright (c) 2018 fuzun
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Game.h"

#include <QSound>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QSettings>
#include <QEasingCurve>
#include <QTimer>

#include "MainWindow/MainWindow.h"
#include "View/View.h"
#include "Bird/Bird.h"
#include "Button/Button.h"
#include "Scene/Scene.h"
#include "Physics/Physics.h"
#include "Sound/Sound.h"

#ifndef AI_DISABLED
#include "AI/AI.h"
#endif

Game::Game(View *GraphicsView, QSettings *cfg, QSettings *settings, int windowWidth, int windowHeight)
    : graphicsView(GraphicsView), screenWidth(windowWidth), screenHeight(windowHeight), config(cfg), registry(settings)
{
    scoreRecord = 0;
    score = 0;

    gameFinished = 0;
    gameStarted = 0;
    gameActuallyStarted = 0;

    birdClosestPipe = 1;

    aiPlays = false;
    ai = nullptr;

    scaleFactor = GAME_DEFAULT_SCALEFACTOR;
    soundEnabled = GAME_DEFAULT_SOUND_ENABLED;

    sound_die = new Sound(SND_DIE, this);
    sound_hit = new Sound(SND_HIT, this);
    sound_point = new Sound(SND_POINT, this);
    sound_swooshing = new Sound(SND_SWOOSHING, this);
    sound_wing = new Sound(SND_WING, this);

    loadConfiguration();

    scene = new Scene(this, QRectF(0, 0, screenWidth, screenHeight));

    physics = new Physics(this, physicsTickRate, physicsComplexAnalysis, true, physicsSpeedFactor, physicsDisableCollisionDetection);
}

Game::~Game()
{
    AIDisable();
    delete physics;
    delete scene;

    delete sound_die;
    delete sound_hit;
    delete sound_point;
    delete sound_swooshing;
    delete sound_wing;
}

void Game::loadConfiguration()
{
    scaleFactor = config->value(CONFIG_SCALEFACTOR, scaleFactor).toReal();

    soundEnabled = registry->value(CONFIG_SOUNDENABLED, soundEnabled).toBool();
    scoreRecord = registry->value(CONFIG_SCORE_RECORD, 0).toInt();

    // config->beginGroup(CONFIG_GENERAL);
    soundEnabled = config->value(CONFIG_SOUNDENABLED, soundEnabled).toBool();
    // config->endGroup();

    config->beginGroup(CONFIG_PHYSICS);
    physicsTickRate = config->value(CONFIG_PHYSICS_TICKRATE, PHYSICS_DEFAULT_TICKRATE).toInt();
    physicsComplexAnalysis = config->value(CONFIG_PHYSICS_COMPLEXANALYSIS, PHYSICS_COMPLEXANALYSIS_ENABLED).toBool();
    physicsSpeedFactor = config->value(CONFIG_PHYSICS_SPEEDFACTOR, PHYSICS_DEFAULT_SPEEDFACTOR).toReal();
    physicsDisableCollisionDetection = config->value(CONFIG_PHYSICS_DISABLECOLLISIONDETECTION, PHYSICS_DEFAULT_DISABLECOLLISIONDETECTION).toBool();
    config->endGroup();

    config->beginGroup(CONFIG_AI);
    aiNeuronCount = config->value(CONFIG_AI_NEURONCOUNT, AI_DEFAULT_NEURONCOUNT).toInt();
    aiBatchSize = config->value(CONFIG_AI_BATCHSIZE, AI_DEFAULT_BATCHSIZE).toInt();
    aiEpochs = config->value(CONFIG_AI_EPOCHS, AI_DEFAULT_EPOCHS).toInt();
    aiUpdateInterval = config->value(CONFIG_AI_UPDATEINTERVAL, AI_DEFAULT_UPDATEINTERVAL).toInt();
    aiClickThreshold = config->value(CONFIG_AI_CLICKTHRESHOLD, AI_DEFAULT_CLICKTHRESHOLD).toFloat();
    config->endGroup();
}

int Game::getScore()
{
    return score;
}

int Game::getScoreRecord()
{
    return scoreRecord;
}

int Game::getScreenHeight()
{
    return screenHeight;
}

int Game::getScreenWidth()
{
    return screenWidth;
}

qreal Game::getScaleFactor()
{
    return scaleFactor;
}

void Game::clickEvent()
{
    if(gameActuallyStarted)
    {
        if(!isGameStarted())
        {
            scene->bird->stopOscillate();

            scene->fadeGroup(GROUP_NEWROUND, false, 100);

            if(physics)
                physics->switchOnlyGroundMove();

            gameStarted = true;
        }
        else
        {
#ifndef AI_DISABLED
        if(ai)
            ai->birdTriggered();
#endif
        }

        if(scene->isGroupVisible(GROUP_NEWROUND))
            scene->fadeGroup(GROUP_NEWROUND, false, 5);

        scene->bird->rise();

        sound_wing->playIfEnabled();

        return;
    }
}

bool Game::isSoundEnabled()
{
    return soundEnabled;
}

void Game::soundDisable()
{
    soundEnabled = false;
    registry->setValue(CONFIG_SOUNDENABLED, soundEnabled);
}

void Game::soundEnable()
{
    soundEnabled = true;
    registry->setValue(CONFIG_SOUNDENABLED, soundEnabled);
}

bool Game::isAIEnabled()
{
    if(ai == nullptr)
        return false;
    else
        return true;
}

void Game::AIEnable()
{
#ifndef AI_DISABLED
    if(!isAIEnabled())
    {

        ai = new AI(this, aiNeuronCount, aiBatchSize, aiEpochs, aiUpdateInterval, aiClickThreshold);

        for(int k = 0; k < GROUP_MAX_ITEM_COUNT; k++) // This method should change in future!
        {
            if(scene->group_item[GROUP_ROUNDEND][k] == nullptr)
            {
                scene->group_item[GROUP_ROUNDEND][k] = scene->item_button_AIPlay;
                scene->group_item[GROUP_ROUNDEND][k + 1] = nullptr;
                break;
            }
        }
    }
#endif
}

void Game::AIDisable()
{
#ifndef AI_DISABLED
    if(isAIEnabled())
    {
        delete ai;
        ai = nullptr;
    }
#endif
}

void Game::prepareNewRound()
{
    scene->flash(Qt::black, 500, QEasingCurve::Linear);

    QTimer::singleShot(550, [this]() {
#ifndef AI_DISABLED
             if(ai)
             {
                if(!ai->trainingFinished)
                    ai->stopTrain();
                ai->clearData();
             }
#endif

             int random1 = Physics::randInt(0, 2);
             int random2 = Physics::randInt(0, 1);

             if(random1 == 0)
                 scene->bird->setColor(Bird::BirdTypes::yellow);
             else if(random1 == 1)
                 scene->bird->setColor(Bird::BirdTypes::blue);
             else // == 2
                 scene->bird->setColor(Bird::BirdTypes::red);

             if(random2 == 0)
             {
                  graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_DAY).scaled(screenWidth,screenHeight)));
             }
             else // == 1
             {
                  graphicsView->setBackgroundBrush(QBrush(QPixmap(IMG_BACKGROUND_NIGHT).scaled(screenWidth,screenHeight)));
             }

             scene->fadeGroup(GROUP_NEWROUND, true, 1, GROUP_ROUNDEND);


             delete physics;
             physics = new Physics(this, physicsTickRate, physicsComplexAnalysis, false, physicsSpeedFactor, physicsDisableCollisionDetection);

             score = -1;
             updateScore();

             gameStarted = false;

             scene->bird->setPos(scene->bird->boundingRect().width() * 2.75, POS_Y_LOGO(screenHeight) + QPixmap(IMG_BIRD_YELLOW_UP).height() * 5);

             prepareFirstGame();

             scene->bird->setRotation(0);

             physics->start();
             physics->switchOnlyGroundMove();
    });
}

void Game::prepareFirstGame()
{
    scene->bird->startOscillate();

    gameFinished = false;
    gameActuallyStarted = true;
}


void Game::gameOver()
{
    physics->stop();

    if(score > scoreRecord)
    {
        registry->setValue(CONFIG_SCORE_RECORD, score);
        scoreRecord = score;
    }

    if(soundEnabled)
    {
        sound_die->playIfEnabled();
        sound_hit->playIfEnabled();
    }

    scene->gameOver(score, scoreRecord);

    gameFinished = true;
    gameActuallyStarted = false;
    birdClosestPipe = 1;

#ifndef AI_DISABLED
    if(ai)
    {
        aiPlays = false;
        QTimer::singleShot(500, [this]() {
            ai->train();
        });
    }
#endif
}


bool Game::isGameFinished()
{
    return gameFinished;
}

bool Game::isGameStarted()
{
    return gameStarted;
}

bool Game::isGameActuallyStarted()
{
    return gameActuallyStarted;
}

void Game::updateScore()
{
    if(score != -1)
        sound_point->playIfEnabled();

    ++score;

    scene->updateScore(score);
}
