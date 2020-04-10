#include "svgsaver.h"

void SvgSaver::save(Scene *scene, QString path, int width, int height) {
    QSvgGenerator generator;
    /** Устанавливаем путь к файлу  +  размер области */
    generator.setFileName(path);
    generator.setSize(QSize(width, height));
    generator.setViewBox(QRect(0, 0, width, height));

    /** Титульное название документа + описание  */
    generator.setTitle(Scene::trUtf8("SVG Example"));
    generator.setDescription(Scene::trUtf8("File created by SVG Example"));

    QPainter painter;
    /** Устанавливаем устройство/объект в котором будем производить отрисовку */
    painter.begin(&generator);

    /** Отрисовываем содержимое сцены с помощью painter в целевое устройство/объект */
    scene->render(&painter);
    painter.end();
}