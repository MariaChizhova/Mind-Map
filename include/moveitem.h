#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>

enum itemState {
    IDRAW, IMOVE
};

class MoveItem : public QObject, public QGraphicsItem {
public:
    explicit MoveItem(QObject *parent = nullptr);

    ~MoveItem() override;

signals:

public:
    QColor itemColor;

    itemState state = IDRAW;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MOVEITEM_H
