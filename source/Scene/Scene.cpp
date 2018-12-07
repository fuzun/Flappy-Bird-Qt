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

#include "Scene.h"

#include <QTransform>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QPainter>

#include "Game/Game.h"
#include "View/View.h"
#include "Bird/Bird.h"
#include "Button/Button.h"


Scene::Scene(Game *parent_game, const QRectF& rect) : QGraphicsScene(rect), game(parent_game)
{
    QPainter _painter;

    flashStatus = false;

    isClickAvailable[0] = true;
    isClickAvailable[1] = true;

    QPixmap background(IMG_BACKGROUND_DAY);
    background = background.scaled(game->getScreenWidth(), game->getScreenHeight());
    game->graphicsView->setBackgroundBrush(QBrush(background));

    game->graphicsView->setScene(this);
    game->graphicsView->setSceneRect(sceneRect());


    QPixmap pixmap_logo(IMG_LOGO);
    PIXMAP_SCALE(pixmap_logo, game->getScaleFactor())
    item_pixmap_logo = new QGraphicsPixmapItem(pixmap_logo);
    item_pixmap_logo->setPos((game->getScreenWidth() / 2) - (pixmap_logo.width() / 2), POS_Y_LOGO(game->getScreenHeight()));

    QPixmap pixmap_ground(IMG_GROUND_SEGMENT);
    PIXMAP_SCALE(pixmap_ground, game->getScaleFactor())
    groundImage = QImage(game->getScreenWidth() * 2, pixmap_ground.height(), QImage::Format_RGB32);
    groundImage.fill(0);
    groundPainter = new QPainter();
    groundPainter->begin(&groundImage);
    int _indicator = 0;
    int _counter = 0;
    for(; _counter < ((game->getScreenWidth() * 2) / pixmap_ground.width()); ++_counter)
    {
        groundPainter->drawPixmap(_indicator, 0, pixmap_ground.width(), pixmap_ground.height(), pixmap_ground);
        _indicator += pixmap_ground.width();
    }
    groundPainter->end();

    QImage buffer((_counter - 1) * pixmap_ground.width(), pixmap_ground.height(), QImage::Format_RGB32);
    buffer = groundImage.copy(0,0,(_counter - 1) * pixmap_ground.width(), pixmap_ground.height());
    groundImage = buffer.scaledToWidth(groundImage.width());
    ground = new QGraphicsPixmapItem(QPixmap::fromImage(groundImage));
    ground->setPos(0, game->getScreenHeight() - groundImage.height() + groundImage.height() / 7);

    QPixmap pixmap_play(IMG_BUTTON_PLAY);
    PIXMAP_SCALE(pixmap_play, game->getScaleFactor())
    item_button_play = new Button(game, pixmap_play, ButtonFuncs::play);
    item_button_play->setPos(game->getScreenWidth() / 2 - pixmap_play.width() * 1.2, ground->y() - pixmap_play.height());

    QPixmap pixmap_about(IMG_BUTTON_ABOUT);
    PIXMAP_SCALE(pixmap_about, game->getScaleFactor())
    item_button_about = new Button(game, pixmap_about, ButtonFuncs::about);
    item_button_about->setPos(game->getScreenWidth() - item_button_play->x() - pixmap_about.width(), item_button_play->y());

    QPixmap pixmap_soundEnabled(IMG_SOUND_ENABLED);
    QPixmap pixmap_soundDisabled(IMG_SOUND_DISABLED);
    PIXMAP_SCALE(pixmap_soundDisabled, game->getScaleFactor());
    PIXMAP_SCALE(pixmap_soundEnabled, game->getScaleFactor());
    if(game->isSoundEnabled())
    {
        item_button_sound = new Button(game, pixmap_soundEnabled, ButtonFuncs::soundDisable, true, pixmap_soundDisabled, ButtonFuncs::soundEnable);
    }
    else
    {
        item_button_sound = new Button(game, pixmap_soundDisabled, ButtonFuncs::soundEnable, true, pixmap_soundEnabled, ButtonFuncs::soundDisable);
    }
    item_button_sound->setPos(game->getScreenWidth() - pixmap_soundEnabled.width(), 0);

#ifndef AI_DISABLED
    QPixmap pixmap_AIEnabled(IMG_AI);
    PIXMAP_SCALE(pixmap_AIEnabled, game->getScaleFactor());
    item_button_AI = new Button(game, pixmap_AIEnabled, ButtonFuncs::aiEnable);
    item_button_AI->setPos(0, 0);

    //if(game->isAIEnabled())
    //{
        QPixmap pixmap_AIPlay(IMG_AIPLAY);
        PIXMAP_SCALE(pixmap_AIPlay, game->getScaleFactor());
        item_button_AIPlay = new Button(game, pixmap_AIPlay, ButtonFuncs::aiPlay);
        item_button_AIPlay->setPos(0, 0);
        item_button_AIPlay->setVisible(false);
    //}
    //else
    //{
    //    item_button_AIPlay = nullptr;
    //}
#else
    item_button_AI = nullptr;
    item_button_AIPlay = nullptr;
#endif

    QPixmap pixmap_pipe_down(IMG_PIPE_DOWN);
    QPixmap pixmap_pipe_up(IMG_PIPE_UP);
    PIXMAP_SCALE(pixmap_pipe_down, game->getScaleFactor())
    PIXMAP_SCALE(pixmap_pipe_up, game->getScaleFactor())

    pipe[0][0] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[0][1] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[0][2] = new QGraphicsPixmapItem(pixmap_pipe_down);
    pipe[1][0] = new QGraphicsPixmapItem(pixmap_pipe_up);
    pipe[1][1] = new QGraphicsPixmapItem(pixmap_pipe_up);
    pipe[1][2] = new QGraphicsPixmapItem(pixmap_pipe_up);


    QPixmap pixmap_gameInfo(IMG_GAMEINFO);
    PIXMAP_SCALE(pixmap_gameInfo, game->getScaleFactor())
    item_pixmap_gameInfo = new QGraphicsPixmapItem(pixmap_gameInfo);
    item_pixmap_gameInfo->setPos(game->getScreenWidth() / 2 - pixmap_gameInfo.width() / 2, game->getScreenHeight() / 2 - pixmap_gameInfo.height() / 3);
    item_pixmap_gameInfo->setVisible(false);

    QPixmap pixmap_gameReady(IMG_READY);
    PIXMAP_SCALE(pixmap_gameReady, game->getScaleFactor())
    item_pixmap_gameReady = new QGraphicsPixmapItem(pixmap_gameReady);
    item_pixmap_gameReady->setPos(game->getScreenWidth() / 2 - pixmap_gameReady.width() / 2, item_pixmap_gameInfo->y() - pixmap_gameReady.height() * 1.6);
    item_pixmap_gameReady->setVisible(false);

    QPixmap pixmap_gameOver(IMG_GAMEOVER);
    PIXMAP_SCALE(pixmap_gameOver, game->getScaleFactor())
    item_pixmap_gameOver = new QGraphicsPixmapItem(pixmap_gameOver);
    item_pixmap_gameOver->setPos(item_pixmap_logo->pos());
    item_pixmap_gameOver->setVisible(false);

    QPixmap pixmap_scoreBoard(IMG_SCOREBOARD);
    PIXMAP_SCALE(pixmap_scoreBoard, game->getScaleFactor())
    item_pixmap_scoreBoard = new QGraphicsPixmapItem(pixmap_scoreBoard);
    item_pixmap_scoreBoard->setPos(game->getScreenWidth() / 2 - pixmap_scoreBoard.width() / 2, item_pixmap_gameOver->y() + item_pixmap_gameOver->boundingRect().height() + (game->getScreenHeight() / 20.69));
    item_pixmap_scoreBoard->setVisible(false);

    pixmap_bigZero = QPixmap(IMG_BIGNUMBER_ZERO);
    PIXMAP_SCALE(pixmap_bigZero, game->getScaleFactor())
    image_mainScore = QImage(pixmap_bigZero.width() * 3, pixmap_bigZero.height(), QImage::Format_ARGB32);
    image_mainScore.fill(qRgba(0, 0, 0, 0));

    _painter.begin(&image_mainScore);
    _painter.drawPixmap(0, 0, pixmap_bigZero.width(), pixmap_bigZero.height(), pixmap_bigZero);
    _painter.end();
    item_pixmap_score = new QGraphicsPixmapItem(pixmap_bigZero);
    item_pixmap_score->setVisible(false);
    item_pixmap_score->setPos(game->getScreenWidth() / 2 - pixmap_bigZero.width() / 2, pixmap_bigZero.height() * 2);


    pixmap_smallZero = QPixmap(IMG_SMALLNUMBER_ZERO);
    PIXMAP_SCALE(pixmap_smallZero, game->getScaleFactor())
    image_endScore = QImage(pixmap_scoreBoard.width(), pixmap_smallZero.height(), QImage::Format_ARGB32);
    image_endScore.fill(qRgba(0,0,0,0));
    item_pixmap_endScore = new QGraphicsPixmapItem();
    item_pixmap_endScore->setVisible(false);

    item_pixmap_endScoreRecord = new QGraphicsPixmapItem();
    item_pixmap_endScoreRecord->setVisible(false);

    QPixmap pixmap_info(IMG_INFO);
    // PIXMAP_SCALE(pixmap_info, game->getScaleFactor())
    item_pixmap_info = new QGraphicsPixmapItem(pixmap_info);
    item_pixmap_info->setPos(game->getScreenWidth() - pixmap_info.width(), game->getScreenHeight() - pixmap_info.height());

    QPixmap pixmap_bird_raw(IMG_BIRD_YELLOW_UP);
    QPixmap pixmap_bird = pixmap_bird_raw;
    PIXMAP_SCALE(pixmap_bird, game->getScaleFactor())
    QPointF pos_bird(game->getScreenWidth() / 2 - pixmap_bird_raw.width() / 2, item_pixmap_logo->pos().y() + pixmap_bird_raw.height() * 5);
    bird = new Bird(pos_bird, pixmap_bird, game->getScreenHeight() - ground->boundingRect().height(), game->getScreenWidth(), game->getScreenHeight(), game->getScaleFactor());

    // FIX: Use QList instead
    button[0] = item_button_play;
    button[1] = item_button_about;
    button[2] = item_button_sound;
    button[3] = item_button_AI;
    button[4] = item_button_AIPlay;
    button[5] = nullptr;

    // FIX: Use QList instead
    group_item[GROUP_NEWROUND][0] = item_pixmap_gameInfo;
    group_item[GROUP_NEWROUND][1] = item_pixmap_gameReady;
    group_item[GROUP_NEWROUND][2] = item_button_sound;
    group_item[GROUP_NEWROUND][3] = nullptr;

    group_item[GROUP_GAMEPLAY][0] = item_pixmap_gameInfo;
    group_item[GROUP_GAMEPLAY][1] = item_pixmap_gameReady;
    group_item[GROUP_GAMEPLAY][2] = item_pixmap_score;
    group_item[GROUP_GAMEPLAY][3] = item_button_sound;
    group_item[GROUP_GAMEPLAY][4] = nullptr;

    group_item[GROUP_ROUNDEND][0] = item_pixmap_scoreBoard;
    group_item[GROUP_ROUNDEND][1] = item_pixmap_gameOver;
    group_item[GROUP_ROUNDEND][2] = item_button_play;
    group_item[GROUP_ROUNDEND][3] = item_pixmap_endScore;
    group_item[GROUP_ROUNDEND][4] = item_pixmap_endScoreRecord;
    // group_item[GROUP_ROUNDEND][5] = item_button_AIPlay;
    group_item[GROUP_ROUNDEND][5] = nullptr;

    group_item[GROUP_FIRSTSCREEN][0] = item_pixmap_logo;
    group_item[GROUP_FIRSTSCREEN][1] = item_button_play;
    group_item[GROUP_FIRSTSCREEN][2] = item_button_about;
    group_item[GROUP_FIRSTSCREEN][3] = item_button_sound;
    group_item[GROUP_FIRSTSCREEN][4] = item_button_AI;
    group_item[GROUP_FIRSTSCREEN][5] = nullptr;


    addItem(item_pixmap_logo);
    addItem(pipe[0][0]);
    addItem(pipe[0][1]);
    addItem(pipe[0][2]);
    addItem(pipe[1][0]);
    addItem(pipe[1][1]);
    addItem(pipe[1][2]);
    addItem(item_button_about);
    addItem(item_button_sound);
#ifndef AI_DISABLED
    addItem(item_button_AI);
    addItem(item_button_AIPlay);
#endif
    addItem(item_pixmap_gameReady);
    addItem(item_pixmap_gameInfo);
    addItem(bird);
    addItem(ground);
    addItem(item_pixmap_scoreBoard);
    addItem(item_pixmap_gameOver);
    addItem(item_pixmap_endScore);
    addItem(item_pixmap_endScoreRecord);
    addItem(item_button_play);
    addItem(item_pixmap_score);
    addItem(item_pixmap_info);
}

Scene::~Scene()
{
    delete bird;
    delete groundPainter;
}

bool Scene::isGroupVisible(int groupIndex)
{
    return group_item[groupIndex][0]->isVisible();
}

void Scene::gameOver(int score, int scoreRecord)
{
    flash(Qt::white, 70, QEasingCurve::Linear);

    QPixmap reward = QPixmap(IMG_SCOREBOARD);
    if(score >= 10 && score < 20)
        reward = QPixmap(IMG_SCOREBOARD_BRONZE);
    else if(score >= 20 && score < 30)
        reward = QPixmap(IMG_SCOREBOARD_SILVER);
    else if(score >= 30 && score < 40)
        reward = QPixmap(IMG_SCOREBOARD_GOLD);
    else if(score >= 40)
        reward = QPixmap(IMG_SCOREBOARD_PLATINUM);

    PIXMAP_SCALE(reward, game->getScaleFactor())
    item_pixmap_scoreBoard->setPixmap(reward);

    int _pos1;
    item_pixmap_endScore->setPixmap(makeEndingScore(score, &_pos1));
    item_pixmap_endScore->setPos(item_pixmap_scoreBoard->x() + item_pixmap_scoreBoard->boundingRect().width() - ((_pos1 + 1) * pixmap_smallZero.width()) - 22 * game->getScaleFactor(), item_pixmap_scoreBoard->y() + pixmap_smallZero.height() * 2.7);

    int _pos2;
    item_pixmap_endScoreRecord->setPixmap(makeEndingScore(scoreRecord, &_pos2));
    item_pixmap_endScoreRecord->setPos(item_pixmap_endScore->x() - _pos2 * pixmap_smallZero.width() + _pos1 * pixmap_smallZero.width(), item_pixmap_endScore->y() + item_pixmap_endScore->boundingRect().height() + 28.5 * game->getScaleFactor());

    item_button_play->setPos(game->getScreenWidth() / 2 - item_button_play->boundingRect().width() / 2, item_pixmap_scoreBoard->y() + item_pixmap_scoreBoard->boundingRect().height() + 20);

    fadeGroup(GROUP_ROUNDEND, true, 500);
}

QPixmap Scene::makeMainScore(int score)
{
    QPainter painter;
    image_mainScore.fill(qRgba(0, 0, 0, 0));
    painter.begin(&image_mainScore);
    QString strScore = QString::number(score);

    int zeroWidth = pixmap_bigZero.width();
    int zeroHeight = pixmap_bigZero.height();

    QPixmap generatedNumber;
    for(int counter = 0; counter < strScore.length(); ++counter)
    {
        generatedNumber.load(QString(IMG_BIGNUMBER_GENERIC).arg(strScore.mid(counter, 1)));

        if(counter == 0)
            painter.drawPixmap(counter * zeroWidth, 0, zeroWidth, zeroHeight, generatedNumber);
        else
            painter.drawPixmap(counter * zeroWidth - zeroWidth / 9.25, 0, zeroWidth, zeroHeight, generatedNumber);
    }
    painter.end();

    return QPixmap::fromImage(image_mainScore);
}

void Scene::updateScore(int score)
{
    item_pixmap_score->setPixmap(makeMainScore(score));
}

QPixmap Scene::makeEndingScore(int score, int *pos)
{
    QPainter painter;
    QString strScore = QString::number(score);
    image_endScore.fill(qRgba(0, 0, 0, 0));
    painter.begin(&image_endScore);

    int zeroWidth = pixmap_smallZero.width();
    int zeroHeight = pixmap_smallZero.height();

    QPixmap generatedNumber;
    int counter = 0;
    for(; counter < strScore.length(); ++counter)
    {
        generatedNumber.load(QString(IMG_SMALLNUMBER_GENERIC).arg(strScore.mid(counter, 1)));
        painter.drawPixmap(counter * zeroWidth + 3, 0, zeroWidth, zeroHeight, generatedNumber);
    }
    painter.end();

    if(pos)
        *pos = counter;

    return QPixmap::fromImage(image_endScore);
}

void Scene::updateGround()
{
    if(ground->x() <= -(ground->boundingRect().width() / 2))
    {
        groundPainter->begin(&groundImage);
        groundPainter->drawPixmap(groundImage.width(), 0, groundImage.width() / 2, groundImage.height(), QPixmap::fromImage(groundImage.copy(0, 0, groundImage.width() / 2, groundImage.height())));
        groundPainter->drawPixmap(0, 0, ground->boundingRect().width() / 2, ground->boundingRect().height(), QPixmap::fromImage(groundImage.copy(groundImage.width() / 2, 0, groundImage.width() / 2, groundImage.height())));
        groundPainter->end();
        ground->setPixmap(QPixmap::fromImage(groundImage));
        ground->setPos(0, ground->y());
    }
}

void Scene::fadeGroup(int groupIndex, bool show, int duration, int group2Index)
{
    if(!isClickAvailable[0])
        return;

    isClickAvailable[0] = false;

    int endMark = 0;
    while(group_item[groupIndex][endMark] != nullptr)
    {
        endMark++;
    }

    opacityEffectGroup[0] = new QGraphicsOpacityEffect*[endMark];
    opacityAnimGroup[0] = new QPropertyAnimation*[endMark];
    for(int k = 0; k < endMark; k++)
    {
        opacityEffectGroup[0][k] = new QGraphicsOpacityEffect(this);
        opacityAnimGroup[0][k] = new QPropertyAnimation(opacityEffectGroup[0][k], "opacity", this);
        group_item[groupIndex][k]->setGraphicsEffect(opacityEffectGroup[0][k]);

        if(!group_item[groupIndex][k]->isVisible())
        {
            group_item[groupIndex][k]->show();
        }

        group_item[groupIndex][k]->setOpacity(1.0);

        if(show)
        {
            opacityAnimGroup[0][k]->setStartValue(0.0);
            opacityAnimGroup[0][k]->setEndValue(1.0);
        }
        else
        {
            opacityAnimGroup[0][k]->setStartValue(1.0);
            opacityAnimGroup[0][k]->setEndValue(0.0);
        }

        QObject::connect(opacityAnimGroup[0][k], &QPropertyAnimation::finished, [=](){
               group_item[groupIndex][k]->setGraphicsEffect(nullptr);
               if(!show)
               {
                   group_item[groupIndex][k]->hide();
               }
               if(group2Index == -1)
                isClickAvailable[0] = true;
            });

        opacityAnimGroup[0][k]->setEasingCurve(QEasingCurve::Linear);
        opacityAnimGroup[0][k]->setDuration(duration);

        opacityAnimGroup[0][k]->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(group2Index != -1)
    {
        int endMark2 = 0;
        while(group_item[group2Index][endMark2] != nullptr)
        {
            endMark2++;
        }
        opacityEffectGroup[1] = new QGraphicsOpacityEffect*[endMark2];
        opacityAnimGroup[1] = new QPropertyAnimation*[endMark2];


        for(int k = 0; k < endMark2; k++)
        {
            opacityEffectGroup[1][k] = new QGraphicsOpacityEffect(this);
            opacityAnimGroup[1][k] = new QPropertyAnimation(opacityEffectGroup[1][k], "opacity", this);
            group_item[group2Index][k]->setGraphicsEffect(opacityEffectGroup[1][k]);

            if(!group_item[group2Index][k]->isVisible())
            {
                group_item[group2Index][k]->show();
            }

            group_item[group2Index][k]->setOpacity(1.0);

            if(show)
            {
                opacityAnimGroup[1][k]->setStartValue(1.0);
                opacityAnimGroup[1][k]->setEndValue(0.0);
            }
            else
            {
                opacityAnimGroup[1][k]->setStartValue(0.0);
                opacityAnimGroup[1][k]->setEndValue(1.0);
            }

            QObject::connect(opacityAnimGroup[1][k], &QPropertyAnimation::finished, [=](){
                   group_item[group2Index][k]->setGraphicsEffect(nullptr);
                   if(show)
                   {
                       group_item[group2Index][k]->hide();
                   }
                   isClickAvailable[0] = true;
                });

            opacityAnimGroup[1][k]->setEasingCurve(QEasingCurve::Linear);
            opacityAnimGroup[1][k]->setDuration(duration);

            opacityAnimGroup[1][k]->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }

    // Not the best garbage collector but better than nothing...
    // Fix this later!
    QTimer::singleShot(duration + 5, [this, group2Index]() {
        delete[] opacityEffectGroup[0];
        delete[] opacityAnimGroup[0];
        if(group2Index != -1)
        {
            delete[] opacityEffectGroup[1];
            delete[] opacityAnimGroup[1];
        }
    });
}

void Scene::flash(const QColor &color, int duration, const QEasingCurve &curve)
{
    if(!isClickAvailable[1])
        return;

    QImage refImg = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter;

    isClickAvailable[1] = false;

    opacityEffect = new QGraphicsOpacityEffect(this);
    opacityAnim = new QPropertyAnimation(opacityEffect, "opacity", this);

    item_pixmap_flash = new QGraphicsPixmapItem();
    item_pixmap_flash->setGraphicsEffect(opacityEffect);

    flashStatus = false;

    painter.begin(&refImg);
    painter.fillRect(QRect(0, 0, width(), height()), color);
    painter.end();

    item_pixmap_flash->setPixmap(QPixmap::fromImage(refImg));

    addItem(item_pixmap_flash);

    opacityAnim->setStartValue(0.0);
    opacityAnim->setDuration(duration);
    opacityAnim->setEasingCurve(curve);
    opacityAnim->setEndValue(1.0);

    connect(opacityAnim, &QPropertyAnimation::finished, [=](){
        if(flashStatus == false)
        {
            QTimer::singleShot(75, [=]() {
               if(opacityAnim)
               {
                    opacityAnim->setStartValue(1.0);
                    opacityAnim->setEndValue(0.0);
                    opacityAnim->setDuration(duration);
                    opacityAnim->start(QAbstractAnimation::DeleteWhenStopped);
               }
            });
            flashStatus = true;
        }
        else
        {
            removeItem(item_pixmap_flash);
            delete item_pixmap_flash;
            flashStatus = false;
            isClickAvailable[1] = true;
        }
});
    opacityAnim->start();
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if((!isClickAvailable[0] || !isClickAvailable[1]) && !(game->isGameActuallyStarted()))
    {
        event->accept();
        return;
    }

    QPointF pos = event->scenePos();

    for(unsigned int k = 0; k < ARRAY_SIZE(button); ++k)
    {
        QApplication::processEvents();
        if (button[k] == nullptr)
            break;
        if(itemAt(pos, game->graphicsView->transform()) == button[k])
        {
            button[k]->invoke();
            return;
        }
    }

    game->clickEvent();
    event->accept();
}

void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    mousePressEvent(event);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if((!isClickAvailable[0] || !isClickAvailable[1]) && !(game->isGameActuallyStarted()))
    {
        event->accept();
        return;
    }
    game->clickEvent();
    event->accept();
}
