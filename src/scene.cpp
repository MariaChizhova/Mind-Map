#include "menu.h"
#include "scene.h"

#include <utility>


Scene::Scene(QObject *parent) : QGraphicsScene(parent) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    if (state == SDRAW) {
        QPointF pos = event->scenePos();

        auto *item = new MoveItem();
        item->itemColor = color;

        item->setPos(pos);
        addItem(item);

        myItems.emplace_back(item);
    }
}

void Scene::setColor(QColor newColor) {
    color = std::move(newColor);
}

void Scene::setFont(QFont newFont) {
    font = std::move(newFont);
}

void Scene::setWindowColor(const QColor& newColor) {
    setBackgroundBrush(newColor);
}

