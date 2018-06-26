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

#include "Game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    graphicsView = new QGraphicsView(this);

    settings = new QSettings(QApplication::organizationName(), QApplication::applicationName(), this);
    graphicsView->setFixedSize(settings->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), settings->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());

    config = new QSettings(QApplication::applicationDirPath() + "/" + CONFIG_FILENAME, QSettings::IniFormat, this);
    // config->beginGroup(CONFIG_GENERAL);
    if(config->value(CONFIG_FULLSCREEN, 0).toBool())
    {
        screenHeight = QGuiApplication::primaryScreen()->availableSize().height();
        screenWidth = QGuiApplication::primaryScreen()->availableSize().width();
        QTimer::singleShot(250, this, SLOT(showFullScreen()));
    }
    else
    {
        graphicsView->setFixedSize(config->value(CONFIG_SCREENWIDTH, GAME_DEFAULT_SCREENWIDTH).toInt(), config->value(CONFIG_SCREENHEIGHT, GAME_DEFAULT_SCREENHEIGHT).toInt());
        screenHeight = this->height();
        screenWidth = this->width();
    }
    // config->endGroup();

    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setCentralWidget(graphicsView);
    this->adjustSize();

    game = new Game(graphicsView, config, settings, screenWidth, screenHeight);
}


MainWindow::~MainWindow()
{
    settings->setValue(CONFIG_SCREENWIDTH, this->width());
    settings->setValue(CONFIG_SCREENHEIGHT, this->height());
    settings->sync();

    delete game;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // QApplication::processEvents();
    if(game)
        delete game;

    int newWidth = width();
    int newHeight = height();

    graphicsView->setFixedSize(newWidth, newHeight); // TODO: Use layout instead
    graphicsView->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    graphicsView->setMinimumSize(0, 0);

    game = new Game(graphicsView, config, settings, newWidth, newHeight);

    event->accept();
}
