#include <iostream>
#include "menu.h"
#include "scene.h"
#include <QFontDialog>

static int test = 0;

Scene::Scene(QObject *parent) : QGraphicsScene(parent), algo(1920, 1080, 1) {
    algo.fillGraph();
    inText.setStyleSheet("background-color: #13011E; color: white");
    inText.resize(500, 500);
    inText.setWindowTitle("Mind Map");
}

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
        activeItem = new QGraphicsRectItem(0, 0, width, height);
        if (!activeItem)
            return;

        /** Задаем цвет прямоугольнику */
        static_cast<QGraphicsPolygonItem *>(activeItem)->setBrush(color);

        /** Добавляем элемент в сцену */
        activeItem->setZValue(1);
        addItem(activeItem);
        pos.rx() -= 30;
        pos.ry() -= 20;
        activeItem->setPos(pos);
        algo.getRectCoord(pos.rx() + 30, pos.ry() + 20, width, height); // Добавили центр прямоугольника Олесе

        activeItem->setFlag(QGraphicsItem::ItemIsFocusable);
        QGraphicsItemGroup* group = createItemGroup({});
        group->setPos(activeItem->pos());
        group->addToGroup(activeItem);
        group->setHandlesChildEvents(true);
        group->setFlag(QGraphicsItem::ItemIsSelectable, false);
        group->setFlag(QGraphicsItem::ItemIsMovable, false);
        myItems.emplace_back(group);
    }
    if (state == SLINE) {
        focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
        focusItem()->setSelected(true);
        if(selectedItem.first == nullptr) selectedItem.first = selectedItems()[0];
        else{
            selectedItem.second = selectedItems()[0];
            //Получили вектор с точками
            vector<pair<int, int>> points = algo.createShortestPath(this->selectedItem.first->pos().rx(),
                                                                    this->selectedItem.first->pos().ry(),
                                                                    this->selectedItem.second->pos().rx(),
                                                                    this->selectedItem.second->pos().ry());
            //Соединяем точки пока просто линиями
            for (int i = 1; i < points.size(); i++) {
                addLine(points[i - 1].first, points[i - 1].second, points[i].first, points[i].second, QPen(Qt::black));
            }

            //Снимаем пометки с выбранных прямоугольников
            selectedItem = make_pair(nullptr, nullptr);
            for (auto &my_item : myItems) {
                if (my_item->isSelected()){
                    my_item->setSelected(false);
                }
            }
        }
        focusItem()->setSelected(false);
    }
    if (state == STEXT) {
        focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
        focusItem()->setSelected(true);

        //Открытие меню текста
        inText.enterText();
        inText.show();
        inText.hide();
        fontcolor = inText.sceneTextColor;

        //Создание текстового объекта и объединение в группу
        QGraphicsTextItem *text = printText();
        QGraphicsItem *rect = this->selectedItems()[0];
        QGraphicsItemGroup* group = dynamic_cast<QGraphicsItemGroup *>(this->selectedItems()[0]);
        rect->setSelected(false);
        focusItem()->setSelected(false);
        group->addToGroup(text);
        group->setHandlesChildEvents(true);
        group->setFlag(QGraphicsItem::ItemIsSelectable, false);
        group->setFlag(QGraphicsItem::ItemIsMovable, false);
        selectedItems().clear();
        for (auto &my_item : myItems) {
            if (my_item->isSelected()){
                my_item->setSelected(false);
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

QGraphicsTextItem *Scene::printText() {
    QGraphicsTextItem *text = addText(inText.textstr);
    text->setSelected(true);
    text->setZValue(2);
    text->setPos(this->selectedItems()[0]->pos());
    text->setFont(font);
    text->setDefaultTextColor(fontcolor);
    text->setFlag(QGraphicsTextItem::ItemIsMovable);
    return text;
}
