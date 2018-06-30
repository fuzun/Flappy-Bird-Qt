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

#include "StrobeDialog.h"

#ifndef STROBE_DISABLED

#include <QLabel>
#include <QLayout>
#include <QTimer>

#include "strobe-api/strobe/strobe-core.h"

StrobeDialog::StrobeDialog(Strobe_Core *strobe_core, QWidget *parent, int posX, int posY, int interval) : QDialog(parent), strobe(strobe_core)
{
    setMinimumSize(500, 525);

    setWindowTitle("Strobe Info...");

    info = new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(info);

    setLayout(layout);

    setPos(posX, posY);

    show();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateInfo()));
    updateTimer->setInterval(interval);
    updateTimer->start();
}

void StrobeDialog::setInterval(int interval)
{
    updateTimer->setInterval(interval);
}

void StrobeDialog::startUpdate()
{
    if(!updateTimer->isActive())
        updateTimer->start();
}

void StrobeDialog::stopUpdate()
{
    if(updateTimer->isActive())
        updateTimer->stop();
}

void StrobeDialog::setPos(int posX, int posY)
{
    setGeometry(posX, posY, width(), height());
}

void StrobeDialog::updateInfo()
{
    strobe->debugHandler();
    info->setText(QString(strobe->debugStr));
}

#endif
