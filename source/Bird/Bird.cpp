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

#include "Bird.h"

#include <QTimer>
#include <QPropertyAnimation>

Bird::Bird(const QPointF& pos, const QPixmap& pixmap, const qreal &groundStartPosY, int scrWidth, int scrHeight, qreal scaleF)
    : QGraphicsPixmapItem(pixmap), groundYPos(groundStartPosY), scaleFactor(scaleF), screenWidth(scrWidth), screenHeight(scrHeight)
{
    setCacheMode(ItemCoordinateCache);

    setPos(pos);

    birdDesigner = new QTimer(this);
    connect(birdDesigner, SIGNAL(timeout()), this, SLOT(designBird()));

    rotator = new QPropertyAnimation(this, "rotation", this);
    currentRotation = 0;

    yAnimator = new QPropertyAnimation(this, "y", this);
    connect(yAnimator, SIGNAL(finished()), this, SLOT(gravitation()));

    oscillateDirection = 1;
    oscillator = new QPropertyAnimation(this, "pos", this);
    oscillator->setDuration(550);
    oscillator->setEndValue(QPointF(boundingRect().width() * 2.75, y()));
    oscillator->setEasingCurve(QEasingCurve::OutQuad);
    connect(oscillator, SIGNAL(finished()), SLOT(oscillate()));

    wingState = WingStates::up;
    setColor(BirdTypes::yellow);

    birdDesigner->start(75);
}


void Bird::oscillate()
{
    oscillator->setEasingCurve(QEasingCurve::OutCubic);

    if(oscillateDirection)
    {
        oscillator->setEndValue(QPointF(x(), y() + PARAM_BIRD_OSCILLATE_FACTOR));
        oscillateDirection = 0;
    }
    else
    {
        oscillator->setEndValue(QPointF(x(), y() - PARAM_BIRD_OSCILLATE_FACTOR));
        oscillateDirection = 1;
    }
    startOscillate();
}

void Bird::designBird()
{
    QPixmap design;

    if(wingState == WingStates::middle)
    {
        if(wingDirection)
        {
            if(birdType == BirdTypes::red)
                design.load(IMG_BIRD_RED_DOWN);
            else if(birdType == BirdTypes::blue)
                design.load(IMG_BIRD_BLUE_DOWN);
            else
                design.load(IMG_BIRD_YELLOW_DOWN);

            setPixmap(design.scaled(design.size() * scaleFactor));
            wingState = WingStates::down;
            wingDirection = 0;
        }
        else
        {
            if(birdType == BirdTypes::red)
                design.load(IMG_BIRD_RED_UP);
            else if(birdType == BirdTypes::blue)
                design.load(IMG_BIRD_BLUE_UP);
            else
                design.load(IMG_BIRD_YELLOW_UP);

            setPixmap(design.scaled(design.size() * scaleFactor));
            wingState = WingStates::up;
            wingDirection = 1;
        }
    }
    else
    {
        if(birdType == BirdTypes::red)
            design.load(IMG_BIRD_RED_MIDDLE);
        else if(birdType == BirdTypes::blue)
            design.load(IMG_BIRD_BLUE_MIDDLE);
        else
            design.load(IMG_BIRD_YELLOW_MIDDLE);

        setPixmap(design.scaled(design.size() * scaleFactor));
        wingState = WingStates::middle;
    }

}

void Bird::setColor(BirdTypes type)
{
    birdType = type;
}

void Bird::gravitation()
{
    birdDesigner->setInterval(85);

    rotate(90, 675, QEasingCurve::InCubic);

    qreal endPos = groundYPos;
    qreal curPosY = y();

    yAnimator->setStartValue(curPosY);
    yAnimator->setEasingCurve(QEasingCurve::InQuad);
    yAnimator->setEndValue(endPos);


    if (abs(curPosY - endPos) < 0.01)
    {
        birdDesigner->stop();
        yAnimator->stop();
        rotator->stop();
        return;
    }

    yAnimator->setDuration(800);

    yAnimator->start();
}

void Bird::fall()
{
    yAnimator->stop();
    gravitation();
}

void Bird::rotate(const qreal &end, const int& duration, const QEasingCurve& curve)
{
    rotator->setDuration(duration);
    rotator->setStartValue(currentRotation);
    rotator->setEndValue(end);
    rotator->setEasingCurve(curve);
    rotator->start();
}

void Bird::setRotation(qreal angle)
{
       if (abs(currentRotation - angle) > 0.01)
       {
           currentRotation = angle;
           QPointF c = boundingRect().center();
           QTransform t;
           t.translate(c.x(), c.y());
           t.rotate(angle);
           t.translate(-c.x(), -c.y());
           setTransform(t);
       }
}

void Bird::startOscillate()
{
    birdDesigner->start(85);
    oscillator->start();
}

void Bird::stopOscillate()
{
    oscillator->stop();
}

void Bird::rise()
{
    qreal curPosY = y();
    yAnimator->stop();
    yAnimator->setStartValue(curPosY);
    yAnimator->setEasingCurve(QEasingCurve::OutQuad);
    yAnimator->setEndValue(curPosY - (screenHeight / 10));

    yAnimator->setDuration(285);

    yAnimator->start();

    birdDesigner->setInterval(35);

    rotate(-20, 95, QEasingCurve::OutQuad);
}

