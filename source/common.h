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

#define TRUE 1
#define FALSE 0

#define GAME_NAME "Flappy Bird Qt"
#define GAME_VERSION "1.0"
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
#define STROBE_DEFAULT_DIALOG_UPDATEINTERVAL 20 // in milliseconds
#define STROBE_DEFAULT_DIALOG_ENABLED TRUE
#define STROBE_DEFAULT_METHOD 1
#define STROBE_DEFAULT_COOLDOWN_DELAY 3 // in seconds
#define STROBE_DEFAULT_SWAPINTERVAL 0 // in seconds
#define STROBE_DEFAULT_DEVIATION_LIMIT 5.0

#define PHYSICS_ONLYGROUND_SLOW_RATE 2.0
#define PHYSICS_DEFAULT_TICKRATE 5
#define PHYSICS_DEFAULT_SPEEDFACTOR 0.9
#define PHYSICS_DEFAULT_DISABLECOLLISIONDETECTION FALSE
#define PHYSICS_COMPLEXANALYSIS_ENABLED TRUE
#define PHYSICS_UNIT_MOVE (1 / 350.0)
#define PHYSICS_UNIT_MOVE_RATE(reference) ((reference) * PHYSICS_UNIT_MOVE)

#define AI_ENABLED TRUE // Disable AI here
#define AI_DEFAULT_NEURONCOUNT 16
#define AI_DEFAULT_BATCHSIZE 16
#define AI_DEFAULT_EPOCHS 1000
#define AI_DEFAULT_RealtimeLearning FALSE
#define AI_DEFAULT_UPDATEINTERVAL 100
#define AI_DEFAULT_SELFTRAIN FALSE
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
// #define CONFIG_SWAPINTERVAL "SwapInterval"
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
#define CONFIG_STROBE_METHOD "Method"
#define CONFIG_STROBE_COOLDOWN_DELAY "CooldownDelay"
#define CONFIG_STROBE_SWAPINTERVAL "SwapInterval"
#define CONFIG_STROBE_DEVIATION_LIMIT "DeviationLimit"

#define CONFIG_AI "AI"
#define CONFIG_AI_NEURONCOUNT "NeuronCount"
#define CONFIG_AI_BATCHSIZE "BatchSize"
#define CONFIG_AI_EPOCHS "Epochs"
#define CONFIG_AI_REALTIMELEARNING "RealtimeLearning"
#define CONFIG_AI_UPDATEINTERVAL "UpdateInterval"
#define CONFIG_AI_SELFTRAIN "SelfTraining"
#define CONFIG_AI_CLICKTHRESHOLD "ClickThreshold"


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
#define IMG_AI ":/graphics/ai.png"
#define IMG_AIPLAY ":/graphics/aiPlay.png"
#define SND_DIE ":/sounds/die.wav"
#define SND_HIT ":/sounds/hit.wav"
#define SND_POINT ":/sounds/point.wav"
#define SND_SWOOSHING ":/sounds/swooshing.wav"
#define SND_WING ":/sounds/wing.wav"

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
