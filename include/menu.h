#ifndef PROJECT_HSE_MENU_H
#define PROJECT_HSE_MENU_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "scene.h"


class Menu : public QMainWindow {
public:
    Menu(QWidget *parent = 0);
    Scene scene;
    QGraphicsView view;
};

#endif //PROJECT_HSE_MENU_H
