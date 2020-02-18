#ifndef PROJECT_HSE_MENU_H
#define PROJECT_HSE_MENU_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "scene.h"


class Menu : public QMainWindow {
public:
    Menu(QWidget *parent = 0);

    Scene scene;
    QGraphicsView view;

private slots:

    void clickButton();

private:
    QPushButton *clickBtn;
};

#endif //PROJECT_HSE_MENU_H
