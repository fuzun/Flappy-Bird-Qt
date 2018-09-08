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

#ifndef PHYSICS_H
#define PHYSICS_H

#include "common.h"

class Physics
{
public:
    Physics(class Game *parent_game, int tickRate = 5, bool complexAnalyse = 0, bool isOnlyGround = 0, qreal speedFactor = 1.0, bool isCollisionDetectionDisabled = 0);
    virtual ~Physics();

    void start();
    void stop();
    void switchOnlyGroundMove();

    bool isOnlyGround();

    static int randInt(int low, int high);

    typedef struct{
        qreal x;
        qreal y;
        qreal width;
        qreal height;
    }rectangle;

private:
    int pipeCriticX;

    qreal speedfactor;

    void moveGround();
    void movePipes();

    bool collisionDetectionDisabled;
    bool pipeMarkers[4];
    bool markers[3];

    rectangle birdRect;
    rectangle _itemPipe;

    class QTimer *physicsTimer;

    static int pipeCriticXFinder(const class QGraphicsPixmapItem& item_pipe);

    class QTransform *_transform;

protected:
    class Game *game;

    class Bird *bird;

    bool complexAnalysis;
    bool onlyGround;

    int updateInterval;

    virtual bool collisionCheck();
    virtual bool collisionCheckComplex(const class QGraphicsPixmapItem& item_pipe);
};

#endif // PHYSICS_H
