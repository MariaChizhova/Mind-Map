#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu window;
    window.setStyleSheet("background-color: #13011E; color: white");
    window.resize(1920, 1080);
    window.setWindowTitle("Mind Map");
    window.scene.setBackgroundBrush(Qt::white);
    window.show();
    return app.exec();
}
