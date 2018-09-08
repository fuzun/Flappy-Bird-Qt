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

#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include <QGraphicsScene>

class Button;
class QGraphicsOpacityEffect;

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(class Game *parent_game, const QRectF& rect);
    ~Scene();

    QGraphicsPixmapItem *pipe[2][3];
    QGraphicsPixmapItem *ground;

    QGraphicsItem *group_item[8][GROUP_MAX_ITEM_COUNT]; // Must be enough

    class Bird *bird;

    void flash(const QColor& color, int duration, const QEasingCurve& curve);
    void fadeGroup(int groupIndex, bool show, int duration, int group2Index = -1);
    void gameOver(int score, int scoreRecord);
    void updateGround();
    void updateScore(int score);
    bool isGroupVisible(int groupIndex);

    Button *item_button_AIPlay; // Should move to AI

private:
    QPixmap pixmap_bigZero;
    QPixmap pixmap_smallZero;

    QImage image_mainScore;
    QImage image_endScore;
    QImage groundImage;

    bool flashStatus;
    bool isClickAvailable[2];

    class QGraphicsOpacityEffect *opacityEffect;
    class QGraphicsOpacityEffect **opacityEffectGroup[2];

    class QPropertyAnimation *opacityAnim;
    class QPropertyAnimation **opacityAnimGroup[2];

    class QPainter *groundPainter;

protected:
    class Game *game;

    Button *button[32]; // 32 buttons would probably be enough for this kind of game
    Button *item_button_play;
    Button *item_button_about;
    Button *item_button_sound;
    Button *item_button_AI;

    QGraphicsPixmapItem *item_pixmap_gameOver;
    QGraphicsPixmapItem *item_pixmap_scoreBoard;
    QGraphicsPixmapItem *item_pixmap_endScore;
    QGraphicsPixmapItem *item_pixmap_endScoreRecord;
    QGraphicsPixmapItem *item_pixmap_info;
    QGraphicsPixmapItem *item_pixmap_logo;
    QGraphicsPixmapItem *item_pixmap_gameReady;
    QGraphicsPixmapItem *item_pixmap_gameInfo;
    QGraphicsPixmapItem *item_pixmap_score;
    QGraphicsPixmapItem *item_pixmap_flash;

    QPixmap makeMainScore(int score);
    QPixmap makeEndingScore(int score, int *pos);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

};

#endif // SCENE_H
