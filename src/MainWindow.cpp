#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    screenSize = QGuiApplication::primaryScreen()->physicalSize();
    qreal w2 = screenSize.width() * 2.5;
    qreal h2 = screenSize.height() * 2;
    qreal wr = 200;
    qreal hr = 80;
    QPushButton *newFile = new QPushButton("New File", this);
    newFile->setGeometry(w2, h2, wr, hr);
    connect(newFile, &QPushButton::clicked, this, &MainWindow::newFileButton);
    QPushButton *openFile = new QPushButton("Open File", this);
    openFile->setGeometry(w2, h2 + hr , wr, hr);
    connect(openFile, &QPushButton::clicked, this, &MainWindow::openFileButton);
    QPushButton *quitBtn = new QPushButton("Quit", this);
    quitBtn->setGeometry(w2, h2 + 2 * hr, wr, hr);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
}

void MainWindow::newProject() {
    this->hide();
    window = new Menu();
    window->setStyleSheet("background-color: #13011E; color: white");
    window->resize(screenSize.width() * 9, screenSize.height() * 9);
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