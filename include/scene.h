#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include "moveitem.h"


enum scene_state {
    SDRAW, SMOVE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(QColor newColor);

    QColor color;

    QFont font;

    scene_state state = SDRAW;

    std::vector<MoveItem *> my_items;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    MoveItem *m_activeItem;
};

#endif
