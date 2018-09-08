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

#ifndef BIRD_H
#define BIRD_H

#include "common.h"

#include <QObject>
#include <QGraphicsPixmapItem>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)

public:
    Bird(const QPointF &pos, const QPixmap& pixmap, const qreal& groundStartPosY, int scrWidth, int scrHeight, qreal scaleF);

    enum BirdTypes{
        yellow,
        blue,
        red
    };

    void setRotation(qreal angle);
    void startOscillate();
    void stopOscillate();
    void rise();
    void setColor(BirdTypes type);
    void fall();

private:
    enum WingStates{
        up,
        middle,
        down
    };

    WingStates wingState;

    bool wingDirection;
    bool oscillateDirection;

    BirdTypes birdType;

    qreal currentRotation;

    class QTimer *birdDesigner;

    class QPropertyAnimation *yAnimator;
    class QPropertyAnimation *oscillator;
    class QPropertyAnimation *rotator;

private slots:
    void gravitation();
    void designBird();
    void oscillate();

protected:
    qreal groundYPos;
    qreal scaleFactor;

    void rotate(const qreal &end, const int &duration, const QEasingCurve &curve);

    int screenWidth, screenHeight;
};

#endif // BIRD_H
