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
#include <algorithm>

enum sceneState {
    SDRAW, SMOVE, STEXT, SLINE, SDELETE
};

enum pixState {
    PIX, PIX1, PIX2, PIX3, MYPIX
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setWindowColor(QColor newColor);

    void drawRect(QPointF pos);

    void addLine();

    void text();

    void delRect();

    void setLineColor(QColor newColor);

    void drawLine(std::pair<int, int> point1, std::pair<int, int> point2);

    QGraphicsTextItem *printText();

    QColor color = Qt::cyan;

    QFont font;

    QColor fontcolor;
    QPointF lastPos;
    QColor linecolor = "#8f5ae5";

    sceneState state = SDRAW;

    pixState pixstate = PIX;

    std::vector<QGraphicsItemGroup *> myItems;
    //std::map<QGraphicsItemGroup *, int> indexItems;

    QGraphicsPixmapItem *activeItem;

    ShortestPath algo;

    sceneMenu inText;
    QPointF point;

    std::pair<QGraphicsItem *, QGraphicsItem *> selectedItem = std::make_pair(nullptr, nullptr);

    std::map<std::pair<int, int>, std::vector<QGraphicsPathItem *>> allPath;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> allRect;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif