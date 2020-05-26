#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    screenSize = QGuiApplication::primaryScreen()->size();
    qreal w2 = screenSize.width() * 0.45;
    qDebug() << "ScreenSize.width           : " << screenSize.width();
    qreal h2 = screenSize.height() * 0.3;
    qDebug() << "ScreenSize.height           : " << screenSize.height();
    qreal wr = 200;
    qreal hr = 80;
    QPushButton *newFile = new QPushButton(this);
    newFile->setIcon(QIcon(":/icons/New File.png"));
    newFile->setIconSize(QSize(200, 80));
    newFile->setGeometry(w2, h2, wr, hr);
    connect(newFile, &QPushButton::clicked, this, &MainWindow::newFileButton);
    QPushButton *openFile = new QPushButton(this);
    openFile->setIcon(QIcon(":/icons/Open FIle.png"));
    openFile->setIconSize(QSize(200, 80));
    openFile->setGeometry(w2, h2 + hr, wr, hr);
    connect(openFile, &QPushButton::clicked, this, &MainWindow::openFileButton);
    QPushButton *quitBtn = new QPushButton(this);
    quitBtn->setIcon(QIcon(":/icons/Exit.png"));
    quitBtn->setIconSize(QSize(200, 80));
    quitBtn->setGeometry(w2, h2 + 2 * hr, wr, hr);
    connect(quitBtn, &QPushButton::clicked, this, QApplication::quit);
}

void MainWindow::newProject() {
    window = new Menu();
    window->setStyleSheet("background-color: #13011E; color: white");
    window->resize(screenSize.width(), screenSize.height());
    window->setWindowTitle("Mind Map");
    window->scene.setBackgroundBrush(Qt::white);
    int diffsize = 0;
    window->scene.setSceneRect(0, 0, screenSize.width() - diffsize, screenSize.height() - diffsize);
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