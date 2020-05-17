#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    screenSize = QGuiApplication::primaryScreen()->size();
    qreal w2 = screenSize.width() * 0.45;
    qDebug() << "ScreenSize.width           : " << screenSize.width();
    qreal h2 = screenSize.height() * 0.3;
    qDebug() << "ScreenSize.height           : " << screenSize.height();
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
    window = new Menu();
    window->setStyleSheet("background-color: #13011E; color: white");
    window->resize(screenSize.width(), screenSize.height());
    window->setWindowTitle("Mind Map");
    window->scene.setBackgroundBrush(Qt::white);
    window->scene.setSceneRect(0,0, screenSize.width(), screenSize.height());
    window->show();
    this->close();
}

void MainWindow::newFileButton() {
   newProject();
   window->newFileButton();
}

void MainWindow::openFileButton() {
    newProject();
    window->newScene();
    window->openButton();
}