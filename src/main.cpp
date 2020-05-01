#include "MainWindow.h"
#include <QScreen>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setStyleSheet("color: white; background-image: url(:/icons/123.jpg)");
    QSizeF screenSize = QGuiApplication::primaryScreen()->physicalSize();
    window.resize(screenSize.width() * 9, screenSize.height() * 9);
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
