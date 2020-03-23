#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <QPainterPath>

enum sceneState {
    SDRAW, SMOVE, TEXT, SLINE
};

class Scene : public QGraphicsScene {
public:
    explicit Scene(QObject *parent = nullptr);

    void setColor(QColor newColor);

    void setFont(QFont newFont);

    void setWindowColor(QColor newColor);

    void printText();

    void setFontColor(QColor newColor);

    void setText(QString str);

    void printLine();

    QColor color;

    QFont font;

    QColor fontcolor;

    QString textstr;

    sceneState state = SDRAW;

    std::vector<QGraphicsItem *> myItems;

    QGraphicsItem *activeItem;

    std::pair<QPointF, QPointF> posLine = {QPoint(-1, -1), QPoint(-1,-1)};

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif