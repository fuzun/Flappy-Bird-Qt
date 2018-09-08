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

#include "View.h"

#include <QTimer>
#include <QElapsedTimer>
#include <QPaintEvent>
#include <QPainter>

#ifndef STROBE_DISABLED
#include "strobe-api/strobe/strobe-core.h"
#endif

View::View(QWidget *parent, StrobeAPI *strobeAPI) : QGraphicsView(parent), strobe(strobeAPI)
{
    frameCount = 0;
    tick = 0;

    fpsTimer = new QElapsedTimer();
    fpsTimer->start();

#ifndef STROBE_DISABLED
    if(strobe != nullptr)
    {
        strobeFPSUpdater = new QTimer(this);
        strobeFPSUpdater->setInterval(25);
        connect(strobeFPSUpdater, &QTimer::timeout, [this]() {
            strobe->setFPS((double)fps());
        });
        strobeFPSUpdater->start();
    }
#endif
}

View::~View()
{
    delete fpsTimer;
}

void View::paintEvent(QPaintEvent *event)
{
    ++frameCount;

#ifndef STROBE_DISABLED
    if(strobe != nullptr)
    {
        bool show = strobe->strobe();
        if(show)
            QGraphicsView::paintEvent(event);
        else
        {
            QPainter painter(viewport());
            painter.fillRect(event->rect(), Qt::black);
        }
    }
    else
    {
        QGraphicsView::paintEvent(event);
    }
#else
    QGraphicsView::paintEvent(event);
#endif
}

float View::fps()
{
    float elapsedTime = (float)(fpsTimer->elapsed());
    int _frameCount = frameCount;

    if((elapsedTime >= 1000.0))
    {
        fpsTimer->restart();
        frameCount = 0;
    }

    return (1000.0f * _frameCount / elapsedTime);
}
