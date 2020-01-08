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

#include "vector.h"

#define TRUE 1
#define FALSE 0

#define GAME_NAME "Flappy Bird Qt"
#define GAME_VERSION "1.5.2"
#define GAME_DEFAULT_SCREENWIDTH 480
#define GAME_DEFAULT_SCREENHEIGHT 800
#define GAME_DEFAULT_SCALEFACTOR 1.6
#define GAME_DEFAULT_SOUND_ENABLED FALSE
#define GAME_DEFAULT_VIEWPORTUPDATE 1
#define GAME_DEFAULT_OPENGL_ENABLED FALSE
#define GAME_DEFAULT_ANTIALIASING_ENABLED TRUE
#define GAME_DEFAULT_SMOOTHPIXMAPTRANSFORM_ENABLED TRUE
#define GAME_DEFAULT_HQANTIALIASING_ENABLED FALSE
#define GAME_DEFAULT_FPSCAP TRUE

#define GROUP_NEWROUND 0
#define GROUP_GAMEPLAY 1
#define GROUP_ROUNDEND 2
#define GROUP_FIRSTSCREEN 3
#define GROUP_MAX_ITEM_COUNT 16

#define STROBE_ENABLED TRUE
#define STROBE_DEFAULT_DIALOG_UPDATEINTERVAL 50 // in milliseconds
#define STROBE_DEFAULT_DIALOG_ENABLED TRUE
#define STROBE_DEFAULT_MODE 1
#define STROBE_DEFAULT_SWITCHINTERVAL 0 // in seconds
#define STROBE_DIALOG_TITLE "Strobe Info..."
#define STROBE_DIALOG_DEFAULT_WIDTH 500
#define STROBE_DIALOG_DEFAULT_HEIGHT 500

#define PHYSICS_ONLYGROUND_SLOW_RATE 2.0
#define PHYSICS_DEFAULT_TICKRATE 5
#define PHYSICS_DEFAULT_SPEEDFACTOR 0.9
#define PHYSICS_DEFAULT_DISABLECOLLISIONDETECTION FALSE
#define PHYSICS_COMPLEXANALYSIS_ENABLED TRUE
#define PHYSICS_UNIT_MOVE (1 / 350.0)
#define PHYSICS_UNIT_MOVE_RATE(reference) ((reference) * PHYSICS_UNIT_MOVE)

#define AI_ENABLED FALSE // Enable AI here
#define AI_DEFAULT_NEURONCOUNT 16
#define AI_DEFAULT_BATCHSIZE 16
#define AI_DEFAULT_EPOCHS 1000
#define AI_DEFAULT_UPDATEINTERVAL 50
#define AI_DEFAULT_CLICKTHRESHOLD 0.5f


#define CONFIG_SCORE_RECORD "Score_Record"
#define CONFIG_FILENAME "config.ini"
#define CONFIG_GENERAL "General"
#define CONFIG_GRAPHICS "Graphic"
#define CONFIG_FPSCAP "FPSCap"
#define CONFIG_FULLSCREEN "Fullscreen"
#define CONFIG_SCALEFACTOR "ScaleFactor"
#define CONFIG_SCREENWIDTH "ScreenWidth"
#define CONFIG_SCREENHEIGHT "ScreenHeight"
#define CONFIG_SOUNDENABLED "Sound"
#define CONFIG_OPENGL "OpenGL"
#define CONFIG_ANTIALIASING "Antialiasing"
#define CONFIG_SMOOTHPIXMAPTRANSFORM "SmoothPixmapTransform"
#define CONFIG_HQANTIALIASING "HighQualityAntiAliasing"
#define CONFIG_VIEWPORTUPDATE "ViewportUpdateMode"

#define CONFIG_PHYSICS "Physics"
#define CONFIG_PHYSICS_COMPLEXANALYSIS "ComplexAnalyse"
#define CONFIG_PHYSICS_TICKRATE "TickRate"
#define CONFIG_PHYSICS_SPEEDFACTOR "SpeedFactor"
#define CONFIG_PHYSICS_DISABLECOLLISIONDETECTION "DisableCollisionDetection"

#define CONFIG_STROBE "Strobe"
#define CONFIG_STROBE_ENABLED "Enabled"
#define CONFIG_STROBE_DIALOG_UPDATEINTERVAL "DialogUpdateInterval"
#define CONFIG_STROBE_DIALOG_ENABLED "Dialog"
#define CONFIG_STROBE_MODE "Mode"
#define CONFIG_STROBE_SWITCHINTERVAL "SwitchInterval"

#define CONFIG_AI "AI"
#define CONFIG_AI_NEURONCOUNT "NeuronCount"
#define CONFIG_AI_BATCHSIZE "BatchSize"
#define CONFIG_AI_EPOCHS "Epochs"
#define CONFIG_AI_REALTIMELEARNING "RealtimeLearning"
#define CONFIG_AI_UPDATEINTERVAL "UpdateInterval"
#define CONFIG_AI_SELFTRAIN "SelfTraining"
#define CONFIG_AI_CLICKTHRESHOLD "ClickThreshold"


#define PREFIX_IMG ":/graphics/"
#define PREFIX_SND ":/sounds/"

#define IMG_BACKGROUND_DAY PREFIX_IMG "background_day.png"
#define IMG_BACKGROUND_NIGHT PREFIX_IMG "background_night.png"
#define IMG_BIRD_YELLOW_UP PREFIX_IMG "bird_yellow_up.png"
#define IMG_BIRD_YELLOW_MIDDLE PREFIX_IMG "bird_yellow_middle.png"
#define IMG_BIRD_YELLOW_DOWN PREFIX_IMG "bird_yellow_down.png"
#define IMG_BIRD_BLUE_UP PREFIX_IMG "bird_blue_up.png"
#define IMG_BIRD_BLUE_MIDDLE PREFIX_IMG "bird_blue_middle.png"
#define IMG_BIRD_BLUE_DOWN PREFIX_IMG "bird_blue_down.png"
#define IMG_BIRD_RED_UP PREFIX_IMG "bird_red_up.png"
#define IMG_BIRD_RED_MIDDLE PREFIX_IMG "bird_red_middle.png"
#define IMG_BIRD_RED_DOWN PREFIX_IMG "bird_red_down.png"
#define IMG_GROUND_SEGMENT PREFIX_IMG "ground_segment.png"
#define IMG_LOGO PREFIX_IMG "logo.png"
#define IMG_BUTTON_PLAY PREFIX_IMG "play.png"
#define IMG_BUTTON_ABOUT PREFIX_IMG "about.png"
#define IMG_PIPE_DOWN PREFIX_IMG "pipe_down.png"
#define IMG_PIPE_UP PREFIX_IMG "pipe_up.png"
#define IMG_GAMEINFO PREFIX_IMG "gameInfo.png"
#define IMG_READY PREFIX_IMG "ready.png"
#define IMG_GAMEOVER PREFIX_IMG "gameOver.png"
#define IMG_SCOREBOARD PREFIX_IMG "scoreBoard.png"
#define IMG_SCOREBOARD_PLATINUM PREFIX_IMG "scoreBoard_platinum.png"
#define IMG_SCOREBOARD_GOLD PREFIX_IMG "scoreBoard_gold.png"
#define IMG_SCOREBOARD_SILVER PREFIX_IMG "scoreBoard_silver.png"
#define IMG_SCOREBOARD_BRONZE PREFIX_IMG "scoreBoard_bronze.png"
#define IMG_BIGNUMBER_ZERO PREFIX_IMG "0.png"
#define IMG_BIGNUMBER_GENERIC PREFIX_IMG "%1.png"
#define IMG_SMALLNUMBER_ZERO PREFIX_IMG "20.png"
#define IMG_SMALLNUMBER_GENERIC PREFIX_IMG "2%1.png"
#define IMG_INFO PREFIX_IMG "info.png"
#define IMG_SOUND_ENABLED PREFIX_IMG "soundEnabled.png"
#define IMG_SOUND_DISABLED PREFIX_IMG "soundDisabled.png"
#define IMG_AI PREFIX_IMG "ai.png"
#define IMG_AIPLAY PREFIX_IMG "aiPlay.png"
#define SND_DIE PREFIX_SND "die.wav"
#define SND_HIT PREFIX_SND "hit.wav"
#define SND_POINT PREFIX_SND "point.wav"
#define SND_SWOOSHING PREFIX_SND "swooshing.wav"
#define SND_WING PREFIX_SND "wing.wav"


#if STROBE_ENABLED == FALSE
#define STROBE_DISABLED
#endif

#if AI_ENABLED == FALSE
#define AI_DISABLED
#endif

#define ARRAY_SIZE(ARR) (sizeof(ARR) / sizeof(*(ARR)))

#define PARAM_BIRD_OSCILLATE_FACTOR (screenHeight / 40)

#define PIXMAP_SCALE(pixmap, scaleFactor) \
    pixmap = (pixmap).scaled((pixmap).size() * scaleFactor);

#define POS_Y_LOGO(height) (((height) / 2) - ((height) / 4.5))

#endif // COMMON_H
