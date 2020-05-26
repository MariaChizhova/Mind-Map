#include "sceneMenu.h"

sceneMenu::sceneMenu(QWidget *parent) : QMainWindow(parent) {};

bool sceneMenu::enterText() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 18), this, tr("Pick a font"));
    if (ok) {
        qDebug() << "font           : " << font;
        qDebug() << "font weight    : " << font.weight();
        qDebug() << "font family    : " << font.family();
        qDebug() << "font style     : " << font.style();
        qDebug() << "font pointSize : " << font.pointSize();
    } else { return false; }
    sceneTextColor = QColorDialog::getColor(Qt::black, this);
    if (sceneTextColor.isValid()) qDebug() << "Color Chosen : " << sceneTextColor.name();
    else sceneTextColor = Qt::black;
    QString text = QInputDialog::getText(this, tr("Text"), tr("Enter:"),
                                         QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty()) textstr = text;
    else return false;
    return true;
}
