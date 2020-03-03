#include "menu.h"
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    /** Позиция мышки */
    QPointF pos = event->scenePos();

    /** Создаем активный элемент (прямоугольник) */
    if (state == SDRAW) {
        int width = 60;
        int height = 40;
        int originX = event->lastPos().rx() - width / 2;
        int originY = event->lastPos().ry() - height / 2;
        activeItem = new QGraphicsRectItem(originX, originY, width, height);
        if (!activeItem)
            return;

        /** Задаем цвет прямоугольнику */
        static_cast<QGraphicsPolygonItem *>(activeItem)->setBrush(color);

        /** Добавляем элемент в сцену */
        addItem(activeItem);
        activeItem->setPos(pos);
        myItems.emplace_back(activeItem);
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