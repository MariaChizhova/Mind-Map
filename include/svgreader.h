#ifndef PROJECT_HSE_SVGREADER_H
#define PROJECT_HSE_SVGREADER_H

#include <QPen>
#include <QList>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QDomDocument>
#include <QGraphicsRectItem>

class SvgReader {
public:
    SvgReader() {};

    static QList<QGraphicsRectItem *> getElements(const QString filename);

    static QList<QPointF> getCoordofLines(const QString filename);

    static QRectF getSizes(const QString filename);
    static QColor color;
};

#endif //PROJECT_HSE_SVGREADER_H
