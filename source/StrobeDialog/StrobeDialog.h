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

#ifndef STROBEDIALOG_H
#define STROBEDIALOG_H

#include "common.h"

#ifndef STROBE_DISABLED

#include <QDialog>

class StrobeDialog : public QDialog
{
    Q_OBJECT

public:
    StrobeDialog(class StrobeAPI *strobeAPI, QWidget *parent = nullptr, int posX = 0, int posY = 0, int interval = 0);

    void setPos(int posX, int posY);
    void setInterval(int interval);
    void startUpdate();
    void stopUpdate();

private:
    class QLabel *info;

    class QLayout *layout;

    class QTimer *updateTimer;

protected:
    class StrobeAPI *strobe;

private slots:
    void updateInfo();

};


#endif

#endif // STROBE_H
