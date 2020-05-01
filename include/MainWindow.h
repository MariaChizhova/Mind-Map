#ifndef PROJECT_HSE_MAINWINDOW_H
#define PROJECT_HSE_MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QApplication>
#include <menu.h>
#include "MainWindow.h"
#include <QScreen>



class MainWindow: public QMainWindow {
public:
    MainWindow(QWidget *parent = 0);

    ~MainWindow() = default;

private slots:
    void newFileButton();

    void openFileButton();

    void newProject();

    Menu *window;

};
#endif //PROJECT_HSE_MAINWINDOW_H
