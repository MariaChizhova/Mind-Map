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

enum sceneState {
    SDRAW, SMOVE, STEXT, SLINE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(QColor newColor);

    QGraphicsTextItem *printText();

    void setFontColor(QColor newColor);

    QColor color;

    QFont font;

    QColor fontcolor;

    sceneState state = SDRAW;

    std::vector<QGraphicsItemGroup *> myItems;

    std::map<QGraphicsItem *, QGraphicsItemGroup *> itemGroup;

    QGraphicsItem *activeItem;

    std::pair<QPointF, QPointF> posLine = {QPoint(-1, -1), QPoint(-1, -1)};

    ShortestPath algo;

    sceneMenu inText;

    std::pair<QGraphicsItem *, QGraphicsItem *> selectedItem = make_pair(nullptr, nullptr);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif