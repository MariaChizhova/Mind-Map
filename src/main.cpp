#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setStyleSheet("color: white; background-image: url(:/icons/123.jpg)");
    window.resize(window.screenSize.width(), window.screenSize.height());
    qDebug() << "ScreenSize.width           : " << QGuiApplication::primaryScreen()->size().width();
    qDebug() << "ScreenSize.height          : " << QGuiApplication::primaryScreen()->size().height();
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
