#include "moveitem.h"

MoveItem::MoveItem(QObject *parent) :
        QObject(parent), QGraphicsItem() {

}

MoveItem::~MoveItem() = default;

QRectF MoveItem::boundingRect() const {
    return QRectF(-30, -30, 60, 40);
}

//отрисовка item
void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(itemColor);
    painter->setBrush(itemColor);
    painter->drawRect(-30, -30, 60, 40);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //новая позиция
    if (this->state == IMOVE) {
        this->setPos(mapToScene(event->pos()));
    }
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //изменение курсора
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}


