#include <iostream>
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
        activeItem->setZValue(1);
        addItem(activeItem);
        activeItem->setPos(pos);
        activeItem->setFlag(QGraphicsItem::ItemIsFocusable);
        myItems.emplace_back(activeItem);
    }
    if (state == SLINE) {
        focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
        focusItem()->setSelected(true);

        if (this->selectedItems().count() == 2) {
            addLine(this->selectedItems()[0]->pos().rx(), this->selectedItems()[0]->pos().ry(),
                    this->selectedItems()[1]->pos().rx(), this->selectedItems()[1]->pos().ry(), QPen(Qt::black));

            for (auto it:this->selectedItems()) {
                it->setSelected(false);
            }
            this->selectedItems().clear();

            for (auto it:myItems) {
                it->setSelected(false);
                it->setFlag(QGraphicsItem::ItemIsSelectable, 0);
            }
        }
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

void Scene::setFontColor(QColor newColor) {
    fontcolor = newColor;
}

void Scene::printText() {
    QGraphicsTextItem *text = addText(textstr);
    text->setZValue(2);
    text->setPos(100, 200);
    text->setFont(font);
    text->setDefaultTextColor(fontcolor);
    text->setFlag(QGraphicsTextItem::ItemIsMovable);
}

void Scene::setText(QString str) {
    textstr = str;
}

void Scene::printLine() {
    QPointF posFirst;

}
