#include "menu.h"
#include "scene.h"
#include "moveitem.h"
#include <QPainter>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), m_activeItem(nullptr) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
    if(state == DRAW) {
        QPointF pos = event->scenePos();
        auto *item = new MoveItem();
        item->setPos(pos);
        addItem(item);
    }
}

void Scene::setColor(QColor newColor) {
    color = newColor;
}

void Scene::setFont(QFont newFont) {
    font = newFont;
}

void Scene::setWindowColor(QColor newColor) {
    setBackgroundBrush(newColor);
}

