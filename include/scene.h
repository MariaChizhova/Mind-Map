#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <QPainter>
#include "moveitem.h"


enum sceneState {
    SDRAW, SMOVE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(const QColor& newColor);

    QColor color;

    QFont font;

    sceneState state = SDRAW;

    std::vector<MoveItem *> myItems;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif
