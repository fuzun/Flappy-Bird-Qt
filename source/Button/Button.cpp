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

#include "Button.h"

#include <QMessageBox>
#include <QString>
#include <QSound>

#include "Game/Game.h"
#include "Scene/Scene.h"
#include "Sound/Sound.h"

void ButtonFuncs::about(Game *game_instance)
{
    QWidget *gameQObject = dynamic_cast<QWidget *>(game_instance);
    QMessageBox::about(gameQObject, "About...", QString("Flappy Bird Qt by fuzun\nVersion: v%1\n\ngithub.com/fuzun/Flappy-Bird-Qt").arg(QCoreApplication::applicationVersion()));
}

void ButtonFuncs::play(Game *game_instance)
{
    game_instance->sound_swooshing->playIfEnabled();

    if(!game_instance->isGameFinished())
    {
         game_instance->prepareFirstGame();
         game_instance->scene->fadeGroup(GROUP_FIRSTSCREEN, false, 500, GROUP_GAMEPLAY);
    }
    else
    {
        game_instance->prepareNewRound();
    }
}

void ButtonFuncs::soundDisable(Game *game_instance)
{
    game_instance->soundDisable();
}

void ButtonFuncs::soundEnable(Game *game_instance)
{
    game_instance->soundEnable();
}

void ButtonFuncs::aiEnable(Game *game_instance)
{
    game_instance->AIEnable();
    QApplication::processEvents();
    ButtonFuncs::play(game_instance);
}

void ButtonFuncs::aiPlay(Game *game_instance)
{
    game_instance->aiPlays = true;
    ButtonFuncs::play(game_instance);
}



void Button::invoke(Game *parent_game)
{
    bool toggleStatus = (pixmap() == Pixmap);
    if(parent_game == nullptr)
        if(toggle && !toggleStatus)
            buttonFunction2(game);
        else
            buttonFunction(game);
    else
        if(toggle && !toggleStatus)
            buttonFunction2(parent_game);
        else
            buttonFunction(parent_game);

    if(toggle)
        setPixmap(toggleStatus ? Pixmap2 : Pixmap);
}
