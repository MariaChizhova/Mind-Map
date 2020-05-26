#ifndef PROJECT_HSE_SVGSAVER_H
#define PROJECT_HSE_SVGSAVER_H

#include <QtSvg/QSvgGenerator>
#include <QtGui/QPainter>
#include <scene.h>

class SvgSaver {
public:
    SvgSaver() {};

    static void save(Scene *scene, QString path, int width, int height);
};

#endif //PROJECT_HSE_SVGSAVER_H
