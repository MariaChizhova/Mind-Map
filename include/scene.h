#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>

enum sceneState {
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

    sceneState state = SDRAW;

    std::vector<QGraphicsItem *> myItems;

    QGraphicsItem *activeItem;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

};

#endif