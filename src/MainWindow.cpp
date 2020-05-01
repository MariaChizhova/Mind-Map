#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QPushButton *newFile = new QPushButton("New File", this);
    newFile->setGeometry(860, 300, 200, 80);
    connect(newFile, &QPushButton::clicked, this, &MainWindow::newFileButton);
    QPushButton *openFile = new QPushButton("Open File", this);
    openFile->setGeometry(860, 380, 200, 80);
    connect(openFile, &QPushButton::clicked, this, &MainWindow::openFileButton);
    QPushButton *quitBtn = new QPushButton("Quit", this);
    quitBtn->setGeometry(860, 460, 200, 80);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
}

void MainWindow::newProject() {
    this->hide();
    window = new Menu();
    window->setStyleSheet("background-color: #13011E; color: white");
    window->resize(1920, 1080);
    window->setWindowTitle("Mind Map");
    window->scene.setBackgroundBrush(Qt::white);
    window->show();
}

void MainWindow::newFileButton() {
   newProject();
}

void MainWindow::openFileButton() {
    newProject();
    window->newScene();
    window->openButton();
}