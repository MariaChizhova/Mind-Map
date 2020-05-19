#include "menu.h"
#include "scene.h"
#include <algorithm>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
                                algo(int(1920), int(1080), 1) {
    qDebug() << "ScreenSize.width           : " << QGuiApplication::primaryScreen()->size().width();
    qDebug() << "ScreenSize.height          : " << QGuiApplication::primaryScreen()->size().height();
    algo.fillGraph();
    inText.setStyleSheet("background-color: #13011E; color: white");
    int diffsize = 0;
    inText.resize(1920 - diffsize, 1080 - diffsize);
    inText.setWindowTitle("Mind Map");
}

void Scene::drawLine(std::pair<int, int> point1, std::pair<int, int> point2) {
    std::vector<std::pair<int, int>> points = algo.createShortestPath(point1.first,
                                                            point1.second,
                                                            point2.first,
                                                            point2.second);

    int step = 5;
    QPainterPath path;
    path.moveTo(points[step].first, points[step].second);
    for (int i = step; i < points.size() - step; i++) {
        QPointF p(points[i].first, points[i].second);
        QPointF k(points[i + 1].first, points[i + 1].second);
        path.quadTo(p, k);
    }
    QGraphicsPathItem *pathItem = addPath(path, QPen(linecolor, 5));
    allPath[point1].push_back(pathItem);
    allPath[point2].push_back(pathItem);
    allRect[point1].push_back(point2);
    allRect[point2].push_back(point1);
}

void Scene::drawRect(QPointF pos) {
    int width = 80;
    int height = 60;
    algo.setRectWidth(width);
    algo.setRectHeight(height);
    QGraphicsPixmapItem *image = new QGraphicsPixmapItem();

    if (pixstate == MYPIX) {
        QGraphicsRectItem *rectItem = new QGraphicsRectItem(QRect(0, 0, width, height));
        rectItem->setPen(QPen(Qt::gray, 3));
        rectItem->setBrush(Qt::gray);
        rectItem->boundingRect();
        rectItem->setBrush(color);
        activeItem = reinterpret_cast<QGraphicsPixmapItem *>(rectItem);
    } else if (pixstate == PIX) {
        QPixmap pix(":/icons/rectangle-png.png");
        image->setPixmap(pix);
        image->setScale(0.15);
        activeItem = image;
    } else if (pixstate == PIX1) {
        QPixmap pix1(":/icons/exp1.png");
        image->setPixmap(pix1);
        image->setScale(0.15);
        activeItem = image;
    } else if (pixstate == PIX2) {
        QPixmap pix2(":/icons/exp2.png");
        image->setPixmap(pix2);
        image->setScale(0.15);
        activeItem = image;
    } else if (pixstate == PIX3) {
        QPixmap pix3(":/icons/exp3.png");
        image->setPixmap(pix3);
        image->setScale(0.15);
        activeItem = image;
    }
    if (!activeItem)
        return;

    /** Добавляем элемент в сцену */
    activeItem->setZValue(1);
    addItem(activeItem);
    pos.rx() -= width / 2;
    pos.ry() -= height / 2;
    activeItem->setPos(pos);
    algo.getRectCoord(pos.rx() + width / 2, pos.ry() + height / 2, width,
                      height); // Добавили центр прямоугольника Олесе

    activeItem->setFlag(QGraphicsItem::ItemIsFocusable);
    QGraphicsItemGroup *group = createItemGroup({});
    group->setPos(activeItem->pos());
    group->addToGroup(activeItem);
    group->setHandlesChildEvents(true);
    group->setFlag(QGraphicsItem::ItemIsSelectable, false);
    group->setFlag(QGraphicsItem::ItemIsMovable, false);
    myItems.emplace_back(group);
}

void Scene::addLine() {
    focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
    focusItem()->setSelected(true);
    if (selectedItem.first == nullptr) selectedItem.first = selectedItems()[0];
    else {
        selectedItem.second = selectedItems()[0];
        std::cout << selectedItem.first->x() << selectedItem.first->y() << endl;
        std::cout << selectedItem.second->x() << selectedItem.second->y() << endl;
        //Получили вектор с точками
        drawLine({this->selectedItem.first->pos().rx(), this->selectedItem.first->pos().ry()},
                 {this->selectedItem.second->pos().rx(), this->selectedItem.second->pos().ry()});
        //Снимаем пометки с выбранных прямоугольников
        selectedItem = {nullptr, nullptr};
        for (auto &my_item : myItems) {
            if (my_item->isSelected()) {
                my_item->setSelected(false);
            }
        }
    }
    focusItem()->setSelected(false);
}

void Scene::text() {
    focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
    focusItem()->setSelected(true);

    //Открытие меню текста
    if (!inText.enterText()) return;
    inText.show();
    inText.hide();
    fontcolor = inText.sceneTextColor;

    //Создание текстового объекта и объединение в группу
    QGraphicsTextItem *text = printText();
    QGraphicsItem *rect = this->selectedItems()[0];
    QGraphicsItemGroup *group = dynamic_cast<QGraphicsItemGroup *>(this->selectedItems()[0]);
    rect->setSelected(false);
    focusItem()->setSelected(false);
    group->addToGroup(text);
    group->setHandlesChildEvents(true);
    group->setFlag(QGraphicsItem::ItemIsSelectable, false);
    group->setFlag(QGraphicsItem::ItemIsMovable, false);
    selectedItems().clear();
    for (auto &my_item : myItems) {
        if (my_item->isSelected()) {
            my_item->setSelected(false);
        }
    }
};

void Scene::delRect() {
    algo.deleteShape({focusItem()->scenePos().rx() + 40, focusItem()->scenePos().ry() + 25});
    for (auto &path: allPath[{focusItem()->scenePos().rx(), focusItem()->scenePos().ry()}]) {
        if (path != nullptr) {
            removeItem(path);
            path = nullptr;
        }
    }
    focusItem()->hide();
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    /** Позиция мышки */
    QPointF pos = event->scenePos();

    if (state == SDRAW) drawRect(pos);
    else if (focusItem() == nullptr) throw SceneException("Object not selected");
    else {
        if (state == SLINE) addLine();
        if (state == STEXT) text();
        if (state == SMOVE) {
            focusItem()->setCursor(QCursor(Qt::ClosedHandCursor));
            lastPos = focusItem()->scenePos();
            for (auto &path: allPath[{lastPos.rx(), lastPos.ry()}]) {
                if (path != nullptr) {
                    removeItem(path);
                    path = nullptr;
                }
            }
            for (auto &rect:allRect[{lastPos.rx(), lastPos.ry()}]) {
                allRect[rect].erase(remove(allRect[rect].begin(), allRect[rect].end(),
                                           std::make_pair(static_cast<int>(lastPos.rx()), static_cast<int>(lastPos.ry()))));
            }
        }
        if (state == SDELETE) delRect();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (focusItem() == nullptr) return;
    focusItem()->setCursor(QCursor(Qt::ArrowCursor));
    if (lastPos != focusItem()->scenePos()) {
        algo.dragShape({lastPos.rx() + 40, lastPos.ry() + 25},
                       {focusItem()->scenePos().rx() + 40, focusItem()->scenePos().ry() + 25});
        focusItem()->setSelected(false);
        for (auto &rect:allRect[{lastPos.rx(), lastPos.ry()}]) {
            drawLine({focusItem()->scenePos().rx(), focusItem()->scenePos().ry()}, rect);
        }
        allRect[{lastPos.rx(), lastPos.ry()}].clear();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void Scene::setColor(QColor newColor) {
    color = newColor;
}

void Scene::setWindowColor(QColor newColor) {
    setBackgroundBrush(newColor);
}

void Scene::setLineColor(QColor newColor) {
    linecolor = newColor;
}

QGraphicsTextItem *Scene::printText() {
    QGraphicsTextItem *text = addText(inText.textstr);
    text->setSelected(true);
    text->setZValue(2);
    auto tmp = this->selectedItems()[0]->pos();
    tmp.ry() += 15;
    tmp.rx() += 13;
    text->setPos(tmp);
    text->setFont(font);
    text->setDefaultTextColor(fontcolor);
    text->setFlag(QGraphicsTextItem::ItemIsMovable);
    return text;
}

void Scene::setState(sceneState newState) {
    if (newState == SMOVE) {
        state = SMOVE;
        for (auto &my_item : myItems) {
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, true);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    } else if (newState == SDRAW) {
        state = SDRAW;
        for (auto &my_item : myItems) {
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    } else if (newState == STEXT) {
        for (auto &my_item : myItems) {
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
        state = STEXT;
    } else if (newState == SLINE) {
        for (auto &my_item : myItems) {
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
        }
        state = SLINE;
    } else if (newState == SDELETE) {
        state = SDELETE;
        for (auto &my_item : myItems) {
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        }
    }
}
