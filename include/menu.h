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

    QColor mcolor;

    void changeColor(QColor newColor);

    void changeFont(QFont newFont);

private slots:

    void newFileButton();

    void helpButton();

    void colorButton();

    void fontButton();

    void openButton();
};

#endif //PROJECT_HSE_MENU_H
