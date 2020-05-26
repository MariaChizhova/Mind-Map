#include "svgreader.h"
#include "scene.h"

QList<QGraphicsRectItem *> SvgReader::getElements(const QString filename) {
    QList<QGraphicsRectItem *> rectList;
    QDomDocument doc;
    QFile file(filename);

    /** Если файл не открылся или не удалось передать содержимое в QDocDocument, то вернем пустой список */
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return rectList;

    /** Ищем в документе все объекты с тегом g */
    QDomNodeList gList = doc.elementsByTagName("g");
    for (int i = 0; i < gList.size(); i++) {
        QDomNode gNode = gList.item(i);

        /** Ищем в ноде из списка элемент с тегом  rect */
        QDomElement rectangle = gNode.firstChildElement("rect");
        if (!rectangle.isNull()) {
            QGraphicsRectItem *rect = new QGraphicsRectItem();

            /** Этот флаг делает объект перемещаемым */
            rect->setFlag(QGraphicsItem::ItemIsMovable);

            /** Забираем размеры из тега rect */
            QDomElement gElement = gNode.toElement();
            rect->setRect(rectangle.attribute("x").toInt(),
                          rectangle.attribute("y").toInt(),
                          rectangle.attribute("width").toInt(),
                          rectangle.attribute("height").toInt());

            /** Забираем из элемента ноды gNode параметры цветов. Эти параметры храняться в теге g */
            QColor fillColor(gElement.attribute("fill", "#ffffff"));
            fillColor.setAlphaF(gElement.attribute("fill-opacity", "0").toFloat());
            rect->setBrush(QBrush(fillColor));
            QColor strokeColor(gElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(gElement.attribute("stroke-opacity").toFloat());
            rect->setPen(QPen(strokeColor, gElement.attribute("stroke-width", "0").toInt()));

            QString transString = gElement.attribute("transform");
            transString.replace(QString("matrix("), QString(""));
            transString.replace(QString(")"), QString(""));
            QStringList transList = transString.split(",");
            QTransform trans(rect->transform());

            /** Positions of rectanges */
            qreal m11 = transList.at(0).toFloat();    /** Horizontal scaling */
            qreal m12 = transList.at(1).toFloat();    /** Vertical shearing */
            qreal m13 = trans.m13();                    /** Horizontal Projection */
            qreal m21 = transList.at(2).toFloat();   /** Horizontal shearing */
            qreal m22 = transList.at(3).toFloat();   /** vertical scaling */
            qreal m23 = trans.m23();                    /** Vertical Projection */
            qreal m31 = transList.at(4).toFloat();   /** Horizontal Position (DX) */
            qreal m32 = transList.at(5).toFloat();;  /** Vertical Position (DY) */
            qreal m33 = trans.m33();                    /** Addtional Projection Factor */

            trans.setMatrix(m11, m12, m13, m21, m22, m23, m31, m32, m33);
            rect->setTransform(trans);
            rect->setPen(QPen(strokeColor, gElement.attribute("stroke-width", "0").toInt()));

//TODO Поменять размеры и про фон!!!
            /** Не двигать фон */
            if (rectangle.attribute("x").toInt() == 0 &&
                rectangle.attribute("y").toInt() == 0 &&
                rectangle.attribute("width").toInt() == 1920 &&
                rectangle.attribute("height").toInt() == 1080) {
                rect->setFlag(QGraphicsItem::ItemIsMovable, false);
            } else {
                rectList.append(rect);
                //lcolor = rectangle.attribute("fill");
            }
        }
    }
    file.close();
    return rectList;
}

QPair<QList<QPointF>, QList<QColor>> SvgReader::getCoordofLines(const QString filename) {
    bool flag = 1;
    QList<QPointF> coordList;
    QList<QColor> colors;
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return QPair(coordList, colors);

    QDomNodeList pList = doc.elementsByTagName("g");
    for (int i = 0; i < pList.size(); i++) {
        QDomNode pNode = pList.item(i);
        QDomElement pathElement = pNode.firstChildElement("path");
        if (pathElement.isNull()) {
            continue;
        } else {
            auto pElement = pNode.toElement();
            QColor strokeColor(pElement.attribute("stroke", "#000000"));
            strokeColor.setAlphaF(pElement.attribute("stroke-opacity").toFloat());
            QColor color = strokeColor;
            colors.append(color);
            QPointF point;
            QStringList listDotes = pathElement.attribute("d").split(" ");
            QString first = listDotes.at(0);
            QStringList firstElement = first.replace(QString("M"), QString("")).split(",");
            point = QPointF(firstElement.at(0).toInt(), firstElement.at(1).toInt());
            coordList.push_back(point);
            qDebug() << point;
            QStringList dot;
            for (int i = 1; i < listDotes.length() - 1; i++) {
                QString other = listDotes.at(i);
                dot = other.replace(QString("C"), QString("")).split(",");
                qDebug() << dot;
                point = QPointF(dot.at(0).toInt(), dot.at(1).toInt());
                coordList.push_back(point);
            }
            coordList.push_back(QPointF(-1, -1));
            qDebug() << dot;
        }
    }
    file.close();
    qDebug() << "LIST SAVER" << coordList.size();
    return QPair(coordList, colors);
}


QRectF SvgReader::getSizes(const QString filename) {
    QDomDocument doc;
    QFile file(filename);

    /** Если файл не открылся/не удалось передать содержимое в QDocDocument, то вернем значение сцены по умолчанию */
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
        return QRectF(0, 0, 200, 200);

    /** Забираем список элементов с тегом svg. В случае, если список элементов будет не пустой, то заберём размеры графической сцены. */
    QDomNodeList list = doc.elementsByTagName("svg");
    if (list.length() > 0) {
        QDomElement svgElement = list.item(0).toElement();
        QStringList parameters = svgElement.attribute("viewBox").split(" ");
        return QRectF(parameters.at(0).toInt(),
                      parameters.at(1).toInt(),
                      parameters.at(2).toInt(),
                      parameters.at(3).toInt());
    }
    return QRectF(0, 0, 200, 200);
}