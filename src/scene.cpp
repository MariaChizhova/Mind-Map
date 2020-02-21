#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include "menu.h"
#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent), m_activeItem(nullptr) {}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);

    /** Позиция мышки */
    QPointF pos = event->scenePos();
    /** Задаем цвет */
    QColor color = menu.getColor(); // ДАЙТЕ МНЕ СЮДА МОЙ MCOLOR

    /** Создаем активный элемент (прямоугольник) */
    m_activeItem = new QGraphicsRectItem(event->lastPos().rx() - 30, event->lastPos().ry() - 20, 60, 40);

    /** Задаем цвет прямоугольнику */
    static_cast<QGraphicsPolygonItem *>(m_activeItem)->setBrush(color);

    if (!m_activeItem) return;

    /** Добавляем элемент в сцену */
    addItem(m_activeItem);
    m_activeItem->setPos(pos);
}


void Scene::keyPressEvent(QKeyEvent *event) {
    QGraphicsScene::keyPressEvent(event);

    if (!m_activeItem)
        return;

    /** Движение с помощью клавиатуры */
    switch (event->key()) {
        case Qt::Key::Key_Left:
            m_activeItem->moveBy(-5, 0);
            break;
        case Qt::Key::Key_Down:
            m_activeItem->moveBy(0, 5);
            break;
        case Qt::Key::Key_Right:
            m_activeItem->moveBy(5, 0);
            break;
        case Qt::Key::Key_Up:
            m_activeItem->moveBy(0, -5);
            break;
    }
}
