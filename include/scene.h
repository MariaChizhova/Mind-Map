#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <QPainterPath>
#include <path.h>
#include <map>
#include <sceneMenu.h>
#include <QFontDialog>
#include <iostream>
#include <QScreen>

enum sceneState {
    SDRAW, SMOVE, STEXT, SLINE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setWindowColor(QColor newColor);

    QGraphicsTextItem *printText();

    QColor color;

    QFont font;

    QColor fontcolor;

    sceneState state = SDRAW;

    std::vector<QGraphicsItemGroup *> myItems;

   // QGraphicsItem *activeItem;
    QGraphicsPixmapItem *activeItem;

    ShortestPath algo;

    sceneMenu inText;

    std::pair<QGraphicsItem *, QGraphicsItem *> selectedItem = make_pair(nullptr, nullptr);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif