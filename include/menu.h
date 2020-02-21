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

    QColor getColor() const;

    QColor mcolor;

    void changeColor(QColor newcolor);

private slots:

    void clickButton();

    static void helpButton();

    void colorButton();

private:
    QPushButton *clickBtn;
    QPushButton *colorBtn;

};

#endif //PROJECT_HSE_MENU_H
