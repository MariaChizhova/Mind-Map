#include <QApplication>
#include "menu.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Menu window;
    window.scene.setSceneRect(0, 0, 900, 900);
    window.resize(1024, 960);
    window.setWindowTitle("Mind Map");
    window.show();
    return app.exec();
}
