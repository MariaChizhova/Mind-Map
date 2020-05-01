#include "menu.h"
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    algo(QGuiApplication::primaryScreen()->physicalSize().width() * 9,
        QGuiApplication::primaryScreen()->physicalSize().height() * 9, 1) {
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
        int width = 80;
        int height = 50;
        algo.set_rect_width(width);
        algo.set_rect_height(height);
        QPixmap pix(":/icons/rectangle-png.png");
        QGraphicsPixmapItem *image = new QGraphicsPixmapItem();
        image->setPixmap(pix);
        image->setScale(0.15);
        /*
        QGraphicsRectItem *rectItem = new QGraphicsRectItem( QRect( 0, 0, width, height ));
        rectItem->setPen( QPen( Qt::gray, 3 ) );
        rectItem->setBrush( Qt::gray );
        rectItem->boundingRect();
        activeItem = rectItem;*/
        activeItem = image;
        if (!activeItem)
            return;

        /** Задаем цвет прямоугольнику */
        /*  static_cast<QGraphicsPolygonItem *>(activeItem)->setBrush(color);*/

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
    if (state == SLINE) {
        focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
        focusItem()->setSelected(true);
        if (selectedItem.first == nullptr) selectedItem.first = selectedItems()[0];
        else {
            selectedItem.second = selectedItems()[0];
            //Получили вектор с точками
            vector<pair<int, int>> points = algo.createShortestPath(this->selectedItem.first->pos().rx(),
                                                                    this->selectedItem.first->pos().ry(),
                                                                    this->selectedItem.second->pos().rx(),
                                                                    this->selectedItem.second->pos().ry());

            int step = 5;
            QPainterPath path;
            path.moveTo(points[step].first, points[step].second);
            for (int i = step; i < points.size() - step; i++) {
                QPointF p(points[i].first, points[i].second);
                QPointF k(points[i + 1].first, points[i + 1].second);
                path.quadTo(p, k);
            }
            addPath(path, QPen(Qt::darkCyan, 5));

            //Снимаем пометки с выбранных прямоугольников
            selectedItem = make_pair(nullptr, nullptr);
            for (auto &my_item : myItems) {
                if (my_item->isSelected()) {
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
    }
}

void Scene::setColor(QColor newColor) {
    color = newColor;
}

void Scene::setWindowColor(QColor newColor) {
    setBackgroundBrush(newColor);
}

QGraphicsTextItem *Scene::printText() {
    QGraphicsTextItem *text = addText(inText.textstr);
    text->setSelected(true);
    text->setZValue(2);
    auto tmp = this->selectedItems()[0]->pos();
    tmp.ry() += 30;
    text->setPos(tmp);
    text->setFont(font);
    text->setDefaultTextColor(fontcolor);
    text->setFlag(QGraphicsTextItem::ItemIsMovable);
    return text;
}
