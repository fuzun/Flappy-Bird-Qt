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

#include "AI.h"

#ifndef AI_DISABLED

#include <QString>
#include <QTimer>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

#include "Game/Game.h"
#include "Scene/Scene.h"
#include "Bird/Bird.h"


AI::AI(class Game *parent_game, int aiNeuronCount, int aiBatchSize, int aiEpochs, int aiUpdateInterval, float aiClickThreshold)
 : neuronCount(aiNeuronCount), batchSize(aiBatchSize), epochs(aiEpochs), updateInterval(aiUpdateInterval), clickThreshold(aiClickThreshold), game(parent_game)
{
    predictClicked = false;
    curEpoch = 0;
    updateCount = 0;

    epochReset = false;
    trainingFinished = true;

    vector.x = -game->getScreenWidth();
    vector.y = -game->getScreenHeight();

    vectorLine = new QGraphicsLineItem();
    QPen linePen;
    linePen.setColor(Qt::darkRed);
    linePen.setWidth(2);
    vectorLine->setPen(linePen);

    birdSpeedVectorLine = new QGraphicsLineItem();
    QPen linePen2;
    linePen2.setColor(Qt::darkMagenta);
    linePen2.setWidth(2);
    birdSpeedVectorLine->setPen(linePen2);

    predictionBar = new QGraphicsLineItem();
    QPen linePen3;
    linePen3.setColor(Qt::yellow);
    linePen3.setWidth(5);
    predictionBar->setPen(linePen3);

    aiInfo = new QGraphicsTextItem();
    aiInfo->setPlainText(QString("***AI***\n\nNeuron count: %1\nBatch size: %2\nEpochs: %3\nUpdate interval: %4\n").arg(QString::number(neuronCount), QString::number(batchSize), QString::number(epochs), QString::number(updateInterval)));
    aiInfo->setPos(0, game->scene->ground->y() + 35);

    game->scene->addItem(aiInfo);
    game->scene->addItem(vectorLine);
    game->scene->addItem(birdSpeedVectorLine);
    game->scene->addItem(predictionBar);

    birdSpeed = new QTimer();
    birdSpeed->setInterval(10);
    birdOldY = game->scene->bird->y();
    QObject::connect(birdSpeed, &QTimer::timeout, [this]() {
        // Calculate instant speed of the bird
        birdSpeedY = -((game->scene->bird->y() - birdOldY) / birdSpeed->interval());
        birdOldY = game->scene->bird->y();
    });

    updater = new QTimer();
    updater->setInterval(updateInterval);
    QObject::connect(updater, &QTimer::timeout, [this]() {
        if(game->isGameFinished() || !game->isGameStarted())
        {
            vectorLine->setVisible(false);
            birdSpeedVectorLine->setVisible(false);
            predictionBar->setVisible(false);
            birdSpeed->stop();
            return;
        }
        vectorLine->setVisible(true);
        birdSpeedVectorLine->setVisible(true);
        if(game->aiPlays)
            predictionBar->setVisible(true);
        birdSpeed->start();
        update();
    });
    updater->start();

    network << tiny_dnn::fully_connected_layer(3, neuronCount) << tiny_dnn::tanh_layer();
    network << tiny_dnn::fully_connected_layer(neuronCount, neuronCount) << tiny_dnn::tanh_layer();
    network << tiny_dnn::fully_connected_layer(neuronCount, neuronCount) << tiny_dnn::tanh_layer();
    network << tiny_dnn::fully_connected_layer(neuronCount, neuronCount) << tiny_dnn::tanh_layer();
    network << tiny_dnn::fully_connected_layer(neuronCount, 1) << tiny_dnn::sigmoid_layer();
}

AI::~AI()
{
    birdSpeed->stop();
    delete birdSpeed;
    updater->stop();
    delete updater;
    game->scene->removeItem(predictionBar);
    delete predictionBar;
    game->scene->removeItem(birdSpeedVectorLine);
    delete birdSpeedVectorLine;
    game->scene->removeItem(vectorLine);
    delete vectorLine;
    game->scene->removeItem(aiInfo);
    delete aiInfo;
}

Vector2<qreal> AI::update(bool reg)
{
    int index = game->birdClosestPipe;
    Vector2<qreal> start, end, actual;

    end.x = game->scene->pipe[0][index]->x() + game->scene->pipe[0][index]->boundingRect().width();
    end.y = ((game->scene->pipe[0][index]->y() + game->scene->pipe[0][index]->boundingRect().height()) + game->scene->pipe[1][index]->y()) / 2.0f;

    start.x = game->scene->bird->x() + game->scene->bird->boundingRect().width();
    start.y = game->scene->bird->y() + game->scene->bird->boundingRect().height() / 2;

    vectorLine->setLine(end.x, end.y, start.x, start.y);

    actual.y = end.y - start.y;
    actual.x = end.x - start.x;

    float normalX = normalize(actual.x, game->getScreenWidth());
    float normalY = normalize(actual.y, game->getScreenHeight());
    float normalSpeed = normalize(birdSpeedY, game->getScreenHeight());

    qreal birdMiddle = game->scene->bird->x() + game->scene->bird->boundingRect().width() / 2;
    qreal speedStartY = birdSpeedY >= 0 ? game->scene->bird->y() - 25 : game->scene->bird->y() + game->scene->bird->boundingRect().height() + 25;
    // qreal speedEndY = birdSpeedY >= 0 ? speedStartY - normalSpeed * 10000 : speedStartY - normalSpeed * 10000;
    qreal speedEndY = speedStartY - normalSpeed * 10000;
    birdSpeedVectorLine->setLine(birdMiddle, speedStartY, birdMiddle, speedEndY);

    tiny_dnn::vec_t i = {{normalX, normalY, birdSpeedY /* normalSpeed */}};
    tiny_dnn::vec_t o = {0.0f};

    QString text = QString("***Pushed Back!***\n# Vector2D(%1, %2) [to input (correct when output=0.0f)]\n-> Normalized x: %3 - y: %4)\n# Bird y speed: %5 [to input]\n# bool($1$) [to output] -> $2$\nTotal: %6\n").arg(QString::number(actual.x), QString::number(actual.y), QString::number(normalX), QString::number(normalY), QString::number(birdSpeedY), QString::number(updateCount));

    if(reg)
    {
        input.push_back(i);
        output.push_back(o);
        text.replace("$1$", "false").replace("$2$", "0.0f");
    }
    else
    {
        text.replace("$1$", "true").replace("$2$", "1.0f");
    }

    aiInfo->setPlainText(text);

    if(game->aiPlays)
    {
        float prediction;
        bool toClick = predictClick(actual, &prediction);
        aiInfo->setPlainText(aiInfo->toPlainText() + QString("\n***AI Plays***\n#Click Prediction: %1\n").arg(QString::number(prediction)));
        if(!predictClicked && toClick)
        {
            predictClicked = true;
            QApplication::processEvents();
            game->clickEvent();
            aiInfo->setPlainText(aiInfo->toPlainText() + QString("***[AI CLICK]***\n"));
            QTimer::singleShot(50, [this]() {
                predictClicked = false;
                aiInfo->setPlainText(aiInfo->toPlainText().replace("***[AI CLICK]***\n", ""));
            });
        }
        qreal middle = game->scene->ground->y() / 2;
        predictionBar->setLine(10, middle - prediction * middle, 10, middle + prediction * middle);
    }
    ++updateCount;
    return actual;
}


void AI::birdTriggered()
{
    if(!(vector.x == -game->getScreenWidth() && vector.y == -game->getScreenHeight()))
    {
        tiny_dnn::vec_t i = {{normalize(vector.x, game->getScreenWidth()), normalize(vector.y, game->getScreenHeight()), birdSpeedY}};
        tiny_dnn::vec_t o = {1.0f};

        input.push_back(i);
        output.push_back(o);
    }
    vector = update(false);
}

void AI::epochUpdate()
{
    QApplication::processEvents();

    curEpoch++;

    if (curEpoch % 10)
    {
        epochReset = false;
        return;
    }

    if(!(curEpoch % 70))
        epochReset = true;

    double loss = network.get_loss<tiny_dnn::cross_entropy>(input, output);

    if(epochReset)
    {
        aiInfo->setPlainText("***Learning from data!***");
    }

    aiInfo->setPlainText(aiInfo->toPlainText() + QString("\nepoch: %1 / %2 - loss: %3").arg(QString::number(curEpoch), QString::number(epochs), QString::number(loss)));


    if(curEpoch == epochs)
    {
        aiInfo->setPlainText(aiInfo->toPlainText() + "\n***Training has been finished!***");
        trainingFinished = true;
    }
}

void AI::train()
{
    curEpoch = 0;
    aiInfo->setPlainText("***Training has been started!***");
    int fixedBatchSize;
    if(updateCount <= batchSize)
        fixedBatchSize = updateCount;
    else
        fixedBatchSize = batchSize;

    trainingFinished = false;
    network.fit<tiny_dnn::cross_entropy>(optimization, input, output, fixedBatchSize, epochs, []() {}, [this]() {epochUpdate();});
}

float AI::normalize(float x, float limit)
{
    return ((x + limit) / limit - 1.0f) * 5.0f;
}

void AI::clearData()
{
    updateCount = 0;
    input.clear();
    output.clear();
}

void AI::stopTrain()
{
    network.stop_ongoing_training();
    aiInfo->setPlainText("***Training has been stopped!***");
}

bool AI::predictClick(Vector2<qreal> instant_vector, float *prediction_ref)
{
     tiny_dnn::vec_t vec = {{normalize((float)instant_vector.x, game->getScreenWidth()), normalize((float)instant_vector.y, game->getScreenHeight()), birdSpeedY}};
     float predicted = network.predict(vec)[0];

     if(prediction_ref)
        *prediction_ref = predicted;

     return predicted >= clickThreshold ? true : false;
}

#endif
