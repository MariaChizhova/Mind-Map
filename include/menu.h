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
#include <QSvgGenerator>
#include <QFileDialog>
#include <QPainter>
#include <QToolBar>
#include <QGraphicsItem>
#include <QFlags>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QInputDialog>
#include "scene.h"
#include <QGraphicsItemGroup>

class Menu : public QMainWindow {
public:
    Menu(QWidget *parent = 0);

    Scene scene;

    QGraphicsView view;

    QColor mcolor;

    QColor wcolor;

    QColor lcolor;

    void changeColor(const QColor &newColor);

    void changeWindowColor(const QColor &newColor);

    void changeLineColor(const QColor &newColor);

    void newScene();

    void openButton();

    void addImage();

    ~Menu() = default;

    void newFileButton();

private slots:

    void helpButton();

    void colorButton();

    void windowColorButton();

    void lineColorButton();

    void saveButton();

    void addRect();

    void deleteShape();

    void moveRect();

    void enterText();

    void addLine();

    void setCellsPix();
    void setCellsPix1();
    void setCellsPix2();
    void setCellsPix3();
    void setCellsMyPix();

    void restorePath(QList<QPointF> paths);


private:
    QString path;
};

#endif //PROJECT_HSE_MENU_H