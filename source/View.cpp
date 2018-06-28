#include "View.h"

#include <QTimer>
#include <QElapsedTimer>
#include <QPaintEvent>
#include <QPainter>

#ifndef STROBE_DISABLED
#include "strobe-api/strobe/strobe-core.h"
#endif

View::View(QWidget *parent, Strobe_Core *strobe_core) : QGraphicsView(parent), strobe(strobe_core)
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
            QPainter painter(this->viewport());
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
