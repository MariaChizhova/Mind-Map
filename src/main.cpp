#include <QApplication>
#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu window;
    window.scene.setSceneRect(0, 0, 900, 900);
    window.resize(1920, 1080);
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
