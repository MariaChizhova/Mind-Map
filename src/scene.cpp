#include "menu.h"
#include "scene.h"
#include "moveitem.h"
#include <QPainter>
#include <vector>


Scene::Scene(QObject *parent) : QGraphicsScene(parent), m_activeItem(nullptr) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    if (state == SDRAW) {
        QPointF pos = event->scenePos();

        auto *item = new MoveItem();
        item->item_color = color;

        item->setPos(pos);
        addItem(item);

        my_items.emplace_back(item);
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

