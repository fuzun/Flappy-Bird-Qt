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

#ifndef COMMON_H
#define COMMON_H

#include <QApplication>


#define ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(*(ARR)))

#define PARAM_BIRD_OSCILLATE_FACTOR (screenHeight / 40)

#define TRUE 1
#define FALSE 0

#define GAME_NAME "Flappy Bird Qt"
#define GAME_VERSION "1.0"
#define GAME_DEFAULT_SCREENWIDTH 480
#define GAME_DEFAULT_SCREENHEIGHT 800
#define GAME_DEFAULT_SCALEFACTOR 1.6
#define GAME_DEFAULT_SOUND_ENABLED FALSE
#define GAME_DEFAULT_VIEWPORTUPDATE 1
#define GAME_DEFAULT_SWAPINTERVAL 1
#define GAME_DEFAULT_OPENGL_ENABLED FALSE
#define GAME_DEFAULT_ANTIALIASING_ENABLED TRUE
#define GAME_DEFAULT_SMOOTHPIXMAPTRANSFORM_ENABLED TRUE
#define GAME_DEFAULT_HQANTIALIASING_ENABLED FALSE

#define IMG_BACKGROUND_DAY ":/graphics/background_day.png"
#define IMG_BACKGROUND_NIGHT ":/graphics/background_night.png"
#define IMG_BIRD_YELLOW_UP ":/graphics/bird_yellow_up.png"
#define IMG_BIRD_YELLOW_MIDDLE ":/graphics/bird_yellow_middle.png"
#define IMG_BIRD_YELLOW_DOWN ":/graphics/bird_yellow_down.png"
#define IMG_BIRD_BLUE_UP ":/graphics/bird_blue_up.png"
#define IMG_BIRD_BLUE_MIDDLE ":/graphics/bird_blue_middle.png"
#define IMG_BIRD_BLUE_DOWN ":/graphics/bird_blue_down.png"
#define IMG_BIRD_RED_UP ":/graphics/bird_red_up.png"
#define IMG_BIRD_RED_MIDDLE ":/graphics/bird_red_middle.png"
#define IMG_BIRD_RED_DOWN ":/graphics/bird_red_down.png"
#define IMG_GROUND_SEGMENT ":/graphics/ground_segment.png"
#define IMG_LOGO ":/graphics/logo.png"
#define IMG_BUTTON_PLAY ":/graphics/play.png"
#define IMG_BUTTON_ABOUT ":/graphics/about.png"
#define IMG_PIPE_DOWN ":/graphics/pipe_down.png"
#define IMG_PIPE_UP ":/graphics/pipe_up.png"
#define IMG_GAMEINFO ":/graphics/gameInfo.png"
#define IMG_READY ":/graphics/ready.png"
#define IMG_GAMEOVER ":/graphics/gameOver.png"
#define IMG_SCOREBOARD ":/graphics/scoreBoard.png"
#define IMG_SCOREBOARD_PLATINUM ":/graphics/scoreBoard_platinum.png"
#define IMG_SCOREBOARD_GOLD ":/graphics/scoreBoard_gold.png"
#define IMG_SCOREBOARD_SILVER ":/graphics/scoreBoard_silver.png"
#define IMG_SCOREBOARD_BRONZE ":/graphics/scoreBoard_bronze.png"
#define IMG_BIGNUMBER_ZERO ":/graphics/0.png"
#define IMG_BIGNUMBER_GENERIC ":/graphics/%1.png"
#define IMG_SMALLNUMBER_ZERO ":/graphics/20.png"
#define IMG_SMALLNUMBER_GENERIC ":/graphics/2%1.png"
#define IMG_INFO ":/graphics/info.png"
#define IMG_SOUND_ENABLED ":/graphics/soundEnabled.png"
#define IMG_SOUND_DISABLED ":/graphics/soundDisabled.png"
#define SND_DIE ":/sounds/die.wav"
#define SND_HIT ":/sounds/hit.wav"
#define SND_POINT ":/sounds/point.wav"
#define SND_SWOOSHING ":/sounds/swooshing.wav"
#define SND_WING ":/sounds/wing.wav"

#define POS_Y_LOGO(height) (((height) / 2) - ((height) / 4.5))

#define CONFIG_SCORE_RECORD "Score_Record"
#define CONFIG_FILENAME "config.ini"
#define CONFIG_GENERAL "General"
#define CONFIG_GRAPHICS "Graphic"
#define CONFIG_FULLSCREEN "Fullscreen"
#define CONFIG_SCALEFACTOR "ScaleFactor"
#define CONFIG_SCREENWIDTH "ScreenWidth"
#define CONFIG_SCREENHEIGHT "ScreenHeight"
#define CONFIG_SOUNDENABLED "Sound"
#define CONFIG_OPENGL "OpenGL"
#define CONFIG_ANTIALIASING "Antialiasing"
#define CONFIG_SMOOTHPIXMAPTRANSFORM "SmoothPixmapTransform"
#define CONFIG_HQANTIALIASING "HighQualityAntiAliasing"
#define CONFIG_SWAPINTERVAL "SwapInterval"
#define CONFIG_VIEWPORTUPDATE "ViewportUpdateMode"
#define CONFIG_PHYSICS "Physics"
#define CONFIG_PHYSICS_COMPLEXANALYSIS "ComplexAnalyse"
#define CONFIG_PHYSICS_TICKRATE "TickRate"

#define GROUP_NEWROUND 0
#define GROUP_GAMEPLAY 1
#define GROUP_ROUNDEND 2
#define GROUP_FIRSTSCREEN 3

#define PHYSICS_ONLYGROUND_SLOW_RATE 2.0
#define PHYSICS_DEFAULT_TICKRATE 5 // Triggered each 5 msec
#define PHYSICS_COMPLEXANALYSIS_ENABLED TRUE
#define PHYSICS_UNIT_MOVE (1 / 350.0)
#define PHYSICS_UNIT_MOVE_RATE(reference) ((reference) * PHYSICS_UNIT_MOVE)

#define PIXMAP_SCALE(pixmap, scaleFactor) \
    pixmap = (pixmap).scaled((pixmap).size() * scaleFactor);


class QPropertyAnimation; // bird.h scene.h
class QGraphicsPixmapItem; // bird.h physics.h scene.h
class QTimer; // bird.h physics.h
class QPropertyAnimation; // bird.h scene.h
class Bird; // scene.h physics.h

#endif // COMMON_H
