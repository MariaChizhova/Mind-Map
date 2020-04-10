#ifndef PROJECT_HSE_SCENEMENU_H
#define PROJECT_HSE_SCENEMENU_H

#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QColorDialog>
#include <QDebug>
#include <QtWidgets/QFontDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QInputDialog>
#include <QLayout>
#include <QtWidgets/QDialogButtonBox>

class sceneMenu : public QMainWindow {
public:
    explicit sceneMenu(QWidget *parent = 0);

    ~sceneMenu() = default;

public:
    QString textstr;
    QColor sceneTextColor;

public slots:

    void enterText();
};


#endif //PROJECT_HSE_SCENEMENU_H
