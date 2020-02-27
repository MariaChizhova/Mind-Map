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

    /** Создаем активный элемент (прямоугольник) */
    int width = 60;
    int height = 40;
    int originX = event->lastPos().rx() - width / 2;
    int originY = event->lastPos().ry() - height / 2;
    m_activeItem = new QGraphicsRectItem(originX, originY, width, height);

    /** Задаем цвет прямоугольнику */
    static_cast<QGraphicsPolygonItem *>(m_activeItem)->setBrush(color);

    if (!m_activeItem)
        return;

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

void Scene::setColor(QColor newColor) {
    color = newColor;
}

void Scene::setFont(QFont newFont) {
    font = newFont;
}

void Scene::setWindowColor(QColor newColor) {
    setBackgroundBrush(newColor);
}