#ifndef PROJECT_HSE_MENU_H
#define PROJECT_HSE_MENU_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QtCore/QTextStream>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QColorDialog>
#include <QDebug>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "scene.h"
#include <QSvgGenerator>
#include <QFileDialog>
#include <QPainter>
#include <QToolBar>
#include <QGraphicsItem>
#include <QFlags>

class Menu : public QMainWindow {
public:
    Menu(QWidget *parent = 0);

    Scene scene;

    QGraphicsView view;

    QColor mcolor;

    QColor wcolor;

    void changeColor(const QColor &newColor);

    void changeFont(const QFont &newFont);

    void changeWindowColor(const QColor &newColor);

    void newScene();

    ~Menu() = default;

private slots:

    void newFileButton();

    void helpButton();

    void colorButton();

    void fontButton();

    void windowColorButton();

    void saveButton();

    void changeState();

    void openButton();

private:
    QString path;
};

#endif //PROJECT_HSE_MENU_H