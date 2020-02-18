#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QtCore/QTextStream>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include "menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
    /** Добавление иконок */
    QPixmap newpix("new.png");
    QPixmap openpix("open.png");
    QPixmap quitpix("quit.png");
    QPixmap helppix("help.png");

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction(newpix, "&New", this);
    QAction *open = new QAction(openpix, "&Open", this);
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

    /** Помещаем действие в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(open);
    file->addAction(quit);
    help->addAction(about);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    connect(clickBtn, &QPushButton::clicked, this, &Menu::clickButton);

    /**  Штука, чтобы отображались иконки */
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    /** Сочетание клавиш */
    newfile->setShortcut(tr("CTRL+N"));
    open->setShortcut(tr("CTRL+O"));
    quit->setShortcut(tr("CTRL+Q"));
}

void Menu::clickButton() {
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}