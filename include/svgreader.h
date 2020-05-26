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

    static QPair<QList<QPointF>, QList<QColor>> getCoordofLines(const QString filename);

    static QRectF getSizes(const QString filename);
};

#endif //PROJECT_HSE_SVGREADER_H
