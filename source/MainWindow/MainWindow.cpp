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

#include "MainWindow.h"

#include <QDesktopWidget>
#include <QSettings>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QTimer>
#include <QScreen>
#include <QtOpenGL>

#include "View/View.h"
#include "Game/Game.h"

#ifndef STROBE_DISABLED
#include "strobe-api/strobe/strobe-core.h"
#include "StrobeDialog/StrobeDialog.h"
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), strobeDialog(nullptr)
{
    config = new QSettings(QApplication::applicationDirPath() + "/" + CONFIG_FILENAME, QSettings::IniFormat, this);

    bool strobeEnabled;

#ifndef STROBE_DISABLED
    config->beginGroup(CONFIG_STROBE);
    strobeEnabled = config->value(CONFIG_STROBE_ENABLED, STROBE_ENABLED).toBool();
    int strobeMode = config->value(CONFIG_STROBE_MODE, STROBE_DEFAULT_MODE).toInt();
    int strobeDialogUpdateInterval = config->value(CONFIG_STROBE_DIALOG_UPDATEINTERVAL, STROBE_DEFAULT_DIALOG_UPDATEINTERVAL).toInt();
    bool strobeDialogEnabled = config->value(CONFIG_STROBE_DIALOG_ENABLED, STROBE_DEFAULT_DIALOG_ENABLED).toBool();
    int strobeSwitchInterval = config->value(CONFIG_STROBE_SWITCHINTERVAL, STROBE_DEFAULT_SWITCHINTERVAL).toInt();
    config->endGroup();

    if(strobeEnabled || strobeMode == 0)
        strobe = new StrobeCore(strobeMode, strobeSwitchInterval);
    else
        strobe = nullptr;
#else
    strobe = nullptr;
    strobeEnabled = false;
#endif

    settings = new QSettings(QApplication::organizationName(), QApplication::applicationName(), this);

    graphicsView = new View(this, strobe);

    graphicsView->setFixedSize(settings->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), settings->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());

    // config->beginGroup(CONFIG_GENERAL);
    if(config->value(CONFIG_FULLSCREEN, 0).toBool())
    {
        screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
        screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
        QTimer::singleShot(500, this, SLOT(showFullScreen()));
    }
    else
    {
        graphicsView->setFixedSize(config->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), config->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());
        screenHeight = graphicsView->height();
        screenWidth = graphicsView->width();
    }
    // config->endGroup();

    config->beginGroup(CONFIG_GRAPHICS);

    bool gpuRender = config->value(CONFIG_OPENGL, GAME_DEFAULT_OPENGL_ENABLED).toBool();
    if(gpuRender)
    {
        QOpenGLWidget *glWidget = new QOpenGLWidget(this);
        graphicsView->setViewport(glWidget);

        if(strobeEnabled)
        {
            prepareManualViewportUpdate();
        }
        else
        {
            graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        }
    }
    else
    {
        bool fpsCap = config->value(CONFIG_FPSCAP, GAME_DEFAULT_FPSCAP).toBool();
        int _config_viewportupdate = config->value(CONFIG_VIEWPORTUPDATE, GAME_DEFAULT_VIEWPORTUPDATE).toInt();

        if(fpsCap)
        {
            if(_config_viewportupdate == 0)
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
            }
            else if(_config_viewportupdate == 1)
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
            }
            else
            {
                graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
            }
        }
        else
        {
            prepareManualViewportUpdate();
        }

#ifndef STROBE_DISABLED
        if(strobeEnabled)
        {
            strobe->setMode(0);
            strobe->disable();
        }
#endif
    }

    if(config->value(CONFIG_ANTIALIASING, GAME_DEFAULT_ANTIALIASING_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::Antialiasing);
    else
        graphicsView->setRenderHint(QPainter::Antialiasing, 0);
    if(config->value(CONFIG_SMOOTHPIXMAPTRANSFORM, GAME_DEFAULT_SMOOTHPIXMAPTRANSFORM_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    else
        graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, 0);
    if(config->value(CONFIG_HQANTIALIASING, GAME_DEFAULT_HQANTIALIASING_ENABLED).toBool())
        graphicsView->setRenderHint(QPainter::HighQualityAntialiasing);
    else
        graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, 0);

    config->endGroup();

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(graphicsView);
    adjustSize();

    game = new Game(graphicsView, config, settings, screenWidth, screenHeight);

#ifndef STROBE_DISABLED
    if(strobeDialogEnabled && (strobe != nullptr))
    {
        strobeDialog = new StrobeDialog(strobe, this, x() + width() + 20, y(), strobeDialogUpdateInterval);
    }
    else
    {
        strobeDialog = nullptr;
    }
#endif

    resizer = new QTimer(this);
    connect(resizer, SIGNAL(timeout()), this, SLOT(resizeTriggered()));
}

MainWindow::~MainWindow()
{
    settings->setValue(CONFIG_SCREENWIDTH, width());
    settings->setValue(CONFIG_SCREENHEIGHT, height());
    settings->sync();

    delete game;

#ifndef STROBE_DISABLED
    if(strobe != nullptr)
        delete strobe;
#endif
}

void MainWindow::prepareManualViewportUpdate()
{
    graphicsView->setViewportUpdateMode(QGraphicsView::NoViewportUpdate);

    QTimer *renderTimer = new QTimer(this);
    renderTimer->setInterval(0);

    connect(renderTimer, &QTimer::timeout, [this]() {
        // QApplication::processEvents();
        graphicsView->viewport()->update();
    });
    renderTimer->start();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if(!resizer->isActive())
        resizer->start(100);
    resized = true;
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);

#ifndef STROBE_DISABLED
    if(strobeDialog != nullptr)
        strobeDialog->setPos(x() + width() + 20, y());
#endif
}

void MainWindow::resizeTriggered()
{
    if(!resized)
    {
        delete game;

        int newWidth = width();
        int newHeight = height();

        graphicsView->setFixedSize(newWidth, newHeight);
        adjustSize();
        graphicsView->setMinimumSize(GAME_DEFAULT_SCREENWIDTH, GAME_DEFAULT_SCREENHEIGHT);

#ifndef STROBE_DISABLED
         if(strobeDialog != nullptr)
         {
            int availableWidth = QGuiApplication::primaryScreen()->availableSize().width();
            int availableHeight = QGuiApplication::primaryScreen()->availableSize().height();

            if((availableHeight - newHeight < 100) && (availableWidth - newWidth < 100))
                strobeDialog->setPos(availableWidth - strobeDialog->width() - 20, availableHeight - strobeDialog->height() - 20);
            else
                strobeDialog->setPos(x() + newWidth + 20, y());
         }
#endif
        game = new Game(graphicsView, config, settings, newWidth, newHeight);
        resizer->stop();
    }

    resized = false;
}
