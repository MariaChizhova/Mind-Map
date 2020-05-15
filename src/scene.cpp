#include "menu.h"
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
                                algo(int(1920), int(1080), 1) {
    qDebug() << "ScreenSize.width           : " << QGuiApplication::primaryScreen()->size().width();
    qDebug() << "ScreenSize.height          : " << QGuiApplication::primaryScreen()->size().height();
    algo.fillGraph();
    inText.setStyleSheet("background-color: #13011E; color: white");
    inText.resize(1920, 1080);
    inText.setWindowTitle("Mind Map");
}

void Scene::drawRect(QPointF pos) {
    int width = 80;
    int height = 50;
    algo.set_rect_width(width);
    algo.set_rect_height(height);
    QPixmap pix(":/icons/rectangle-png.png");
    QPixmap pix1(":/icons/exp1.png");
    QPixmap pix2(":/icons/exp2.png");
    QPixmap pix3(":/icons/exp3.png");
    QGraphicsPixmapItem *image = new QGraphicsPixmapItem();
    if (pixstate == PIX)
    	image->setPixmap(pix);
    else if (pixstate == PIX1)
        image->setPixmap(pix1);
    else if (pixstate == PIX2)
        image->setPixmap(pix2);
    else if (pixstate == PIX3)
        image->setPixmap(pix3);
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
    //indexItems[group] = myItems.size();
    myItems.emplace_back(group);
}

void Scene::addLine() {
    focusItem()->setFlag(QGraphicsItem::ItemIsSelectable, 1);
    focusItem()->setSelected(true);
    if (selectedItem.first == nullptr) selectedItem.first = selectedItems()[0];
    else {
        selectedItem.second = selectedItems()[0];
        cout << selectedItem.first->x() << selectedItem.first->y() << endl;
        cout << selectedItem.second->x() << selectedItem.second->y() << endl;
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
        addPath(path, QPen(linecolor, 5));

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

void Scene::text() {
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
};

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    /** Позиция мышки */
    QPointF pos = event->scenePos();

    if (state == SDRAW) drawRect(pos);
    if (state == SLINE) addLine();
    if (state == STEXT) text();
    if (state == SMOVE) {
        focusItem()->setCursor(QCursor(Qt::ClosedHandCursor));
        last_pos = focusItem()->scenePos();
    }
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
    cout << focusItem()->scenePos().rx() << " " << focusItem()->scenePos().ry() << endl;
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (focusItem() == nullptr) return;
    focusItem()->setCursor(QCursor(Qt::ArrowCursor));
    if (last_pos != focusItem()->scenePos()) {
        algo.dragShape(make_pair(last_pos.rx(), last_pos.ry()),
                       make_pair(focusItem()->scenePos().rx() + 40, focusItem()->scenePos().ry() + 25));
        focusItem()->setSelected(false);
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