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

#include "common.h"
#ifndef AI_DISABLED

#ifndef AI_H
#define AI_H

#include "tiny_dnn/tiny_dnn.h"

class AI
{
public:
    AI(class Game *parent_game, int aiNeuronCount, int aiBatchSize, int aiEpochs, int aiUpdateInterval, float aiClickThreshold);
    ~AI();

    void birdTriggered();
    void train();
    void clearData();
    void stopTrain();

    bool trainingFinished;

    static float normalize(float x, float limit);

private:
    int neuronCount;
    int batchSize;
    int epochs;
    int updateInterval;
    int curEpoch;
    int updateCount;

    float clickThreshold;
    float birdSpeedY;
    float birdOldY;

    bool realtimeLearn;
    bool selfTrain;
    bool predictClicked;
    bool epochReset;

    Vector2<qreal> vector;

    class QTimer *updater;
    class QTimer *randomPlayer;
    class QTimer *birdSpeed;

    Vector2<qreal> update(bool reg = true);

    bool predictClick(Vector2<qreal> instant_vector, float *prediction_ref = nullptr);

    class QGraphicsLineItem *vectorLine;
    class QGraphicsLineItem *birdSpeedVectorLine;
    class QGraphicsLineItem *predictionBar;
    class QGraphicsTextItem *aiInfo;

    tiny_dnn::network<tiny_dnn::sequential> network;
    std::vector<tiny_dnn::vec_t> input;
    std::vector<tiny_dnn::vec_t> output;
    tiny_dnn::adam optimization;

    void epochUpdate();

protected:
    class Game *game;

};

#endif // AI_H

#endif
