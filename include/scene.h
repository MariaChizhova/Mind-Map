#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newcolor);

    QColor color;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    QGraphicsItem *m_activeItem;

};

#endif
