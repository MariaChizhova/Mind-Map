#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QtCore/QTextStream>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QColorDialog>
#include <QDebug>
#include "menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent) {

    /** Добавление иконок */
    QPixmap newpix("new.png");
    QPixmap savepix("open.png");
    QPixmap quitpix("quit.png");
    QPixmap helppix("help.png");

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction(newpix, "&New", this);
    QAction *save = new QAction(savepix, "&Save", this);
    QAction *quit = new QAction(quitpix, "&Quit", this);
    QAction *about = new QAction("&About", this);

    /** Создаём объект класса QMenu (меню) */
    QMenu *file = menuBar()->addMenu("&File");
    QMenu *edit = menuBar()->addMenu("&Edit");
    QMenu *view = menuBar()->addMenu("&View");
    QMenu *tools = menuBar()->addMenu("&Tools");
    QMenu *help = menuBar()->addMenu(helppix, "&Help");

    /** Кнопка, на которую можно тыкать */
    clickBtn = new QPushButton("Click", this);
    clickBtn->setGeometry(QRect(QPoint(300, 50), QSize(70, 50)));
    colorBtn = new QPushButton("Color", this);
    colorBtn->setGeometry(QRect(QPoint(370, 50), QSize(70, 50)));

    /** Помещаем действие в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(save);
    file->addAction(quit);
    help->addAction(about);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(clickBtn, &QPushButton::clicked, this, &Menu::clickButton);
    connect(about, &QAction::triggered, qApp, Menu::helpButton);
    connect(colorBtn, &QPushButton::clicked, this, &Menu::colorButton);

    /**  Штука, чтобы отображались иконки */
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    /** Сочетание клавиш */
    newfile->setShortcut(tr("CTRL+N"));
    save->setShortcut(tr("CTRL+C"));
    quit->setShortcut(tr("CTRL+Q"));
}

void Menu::clickButton() {
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}

void Menu::helpButton() {
    QTextStream out(stdout);
    out << "HELP ME" << endl;
}

void Menu::colorButton() {
    mcolor = QColorDialog::getColor(Qt::yellow, this);
    if (mcolor.isValid())
        qDebug() << "Color Choosen : " << mcolor.name();
    changeColor(mcolor);
}

QColor Menu::getColor() const {
    qDebug() << "Choosen : " << mcolor.name();
    return mcolor;
}

void Menu::changeColor(QColor newcolor) {
    scene.setColor(newcolor);
}
