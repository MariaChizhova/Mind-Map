#include <QMenu>
#include <QMenuBar>
#include <QGraphicsView>
#include "menu.h"

SimpleMenu::SimpleMenu(QWidget *parent) : QMainWindow(parent) {
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction("&New", this);
    QAction *open = new QAction("&Open", this);
    QAction *quit = new QAction("&Quit", this);

    /** Создаём объект класса QMenu (меню) */
    QMenu *file = menuBar()->addMenu("&File");
    QMenu *edit = menuBar()->addMenu("&Edit");
    QMenu *view = menuBar()->addMenu("&View");
    QMenu *tools = menuBar()->addMenu("&Tools");
    QMenu *help = menuBar()->addMenu("&Help");

    /** Помещаем действие "Quit" (Выход) в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(open);
    file->addAction(quit);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, qApp, QApplication::quit);

    /** Сочетание клавиш */
    newfile->setShortcut(tr("CTRL+N"));
    open->setShortcut(tr("CTRL+O"));
    quit->setShortcut(tr("CTRL+Q"));
}