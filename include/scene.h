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

    void setLineColor(QColor newColor);

    void setColor(QColor newColor);

    void setWindowColor(QColor newColor);

    void setState(sceneState newState);

    QColor linecolor = "#8f5ae5";
    pixState pixstate = PIX;
    ShortestPath algo;
    std::vector<QGraphicsItemGroup *> myItems;
private:

    void drawRect(QPointF pos);

    void addLine();

    void text();

    void delRect();

    void drawLine(pair<int, int> point1, pair<int, int> point2);

    sceneState state = SDRAW;

    QGraphicsTextItem *printText();

    QColor color = Qt::cyan;

    QFont font;

    QColor fontcolor;
    QPointF lastPos;

    QGraphicsPixmapItem *activeItem;

    sceneMenu inText;

    std::pair<QGraphicsItem *, QGraphicsItem *> selectedItem = make_pair(nullptr, nullptr);

    map<pair<int, int>, vector<QGraphicsPathItem *>> allPath;
    map<pair<int, int>, vector<pair<int, int>>> allRect;

    class SceneException : public std::exception {
    private:
        std::string read_error = "";
    public:
        explicit SceneException(std::string error) : read_error(std::move(error)) {}

        const char *what() const noexcept override { return read_error.c_str(); }
    };

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif