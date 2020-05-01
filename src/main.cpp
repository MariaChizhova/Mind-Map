#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setStyleSheet("color: white; background-image: url(:/icons/123.jpg)");
    window.resize(window.screenSize.width(), window.screenSize.height());
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
