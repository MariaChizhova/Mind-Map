#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "moveitem.h"

enum scene_state{
    DRAW, MOVE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(QColor newColor);

    QColor color;

    QFont font;

    scene_state state = DRAW;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

     MoveItem *m_activeItem;
};

#endif
