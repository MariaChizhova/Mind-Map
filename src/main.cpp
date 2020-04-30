#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setStyleSheet("color: white; background-image: url(:/icons/123.jpg)");
    window.resize(1920, 1080);
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
