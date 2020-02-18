#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include "scene.h"


Scene::Scene(QObject *parent)
  : QGraphicsScene(parent),
    m_activeItem(nullptr){
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsScene::mousePressEvent(event);

  QPointF pos = event->scenePos();

  QColor color(255, 0, 0);

  m_activeItem = new QGraphicsRectItem(0, 0, 70, 40);
  static_cast<QGraphicsPolygonItem*>(m_activeItem)->setBrush(color);

  if (nullptr == m_activeItem)
    return;

  addItem(m_activeItem);
  m_activeItem->setPos(pos);
}


void Scene::keyPressEvent(QKeyEvent *event) {
  QGraphicsScene::keyPressEvent(event);

  if (nullptr == m_activeItem)
    return;

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
