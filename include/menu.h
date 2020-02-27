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

    QColor wcolor;

    void changeColor(QColor newColor);

    void changeFont(QFont newFont);

    void changeWindowColor(QColor newColor);

private slots:

    void newFileButton();

    void helpButton();

    void colorButton();

    void fontButton();

    void openButton();

    void windowColorButton();
};

#endif //PROJECT_HSE_MENU_H
