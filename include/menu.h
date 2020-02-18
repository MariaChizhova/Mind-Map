#ifndef PROJECT_HSE_MENU_H
#define PROJECT_HSE_MENU_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "scene.h"


class SimpleMenu : public QMainWindow {

public:
    SimpleMenu(QWidget *parent = 0);
    Scene scene;
    QGraphicsView view;
private:
};

#endif //PROJECT_HSE_MENU_H
