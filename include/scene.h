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

    void drawRect(QPointF pos);

    void drawLine(std::pair<int, int> point1, std::pair<int, int> point2);

private:

    void addLine();

    void text();

    void delRect();

    sceneState state = SDRAW;

    QGraphicsTextItem *printText();

    QColor color = Qt::cyan;

    QFont font;

    QColor fontcolor;
    QPointF lastPos;

    QGraphicsPixmapItem *activeItem;

    sceneMenu inText;

    std::pair<QGraphicsItem *, QGraphicsItem *> selectedItem = std::make_pair(nullptr, nullptr);

    std::map<std::pair<int, int>, std::vector<QGraphicsPathItem *>> allPath;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> allRect;

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