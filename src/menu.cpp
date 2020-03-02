#include <QToolBar>
#include "menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
    /** Добавление иконок. Пропишите свой путь к иконкам */
    QPixmap newpix(":/icons/new.png");
    QPixmap savepix(":/icons/save.png");
    QPixmap quitpix(":/icons/quit.png");
    QPixmap helppix(":/icons/help.png");
    QPixmap colorpix(":/icons/color.png");
    QPixmap fontpix(":/icons/font.png");
    QPixmap openpix(":/icons/open.png");
    QPixmap wincolorpix(":/icons/wincolor.png");
    QPixmap rectanglepix(":/icons/rectangle.png");

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction(newpix, "&New", this);
    QAction *open = new QAction(openpix, "&Open", this);
    QAction *save = new QAction(savepix, "&Save", this);
    QAction *quit = new QAction(quitpix, "&Quit", this);
    QAction *about = new QAction(helppix, "&About", this);
    QAction *color = new QAction(colorpix, "&Color", this);
    QAction *wincolor = new QAction(wincolorpix, "&WinColor", this);
    QAction *font = new QAction(fontpix, "&Font", this);

    /** Создаём объект класса QMenu (меню) */
    QMenu *file = menuBar()->addMenu("&File");
    QMenu *edit = menuBar()->addMenu("&Edit");
    QMenu *view = menuBar()->addMenu("&View");
    QMenu *tools = menuBar()->addMenu("&Tools");
    QMenu *help = menuBar()->addMenu("&Help");

    /** Помещаем действие в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(open);
    file->addAction(save);
    file->addAction(quit);
    help->addAction(about);
    edit->addAction(color);
    edit->addAction(font);
    edit->addAction(wincolor);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, this, QApplication::quit);
    connect(about, &QAction::triggered, this, &Menu::helpButton);
    connect(color, &QAction::triggered, this, &Menu::colorButton);
    connect(wincolor, &QAction::triggered, this, &Menu::windowColorButton);
    connect(newfile, &QAction::triggered, this, &Menu::newFileButton);
    connect(font, &QAction::triggered, this, &Menu::fontButton);
    connect(open, &QAction::triggered, this, &Menu::openButton);
    connect(save, &QAction::triggered, this, &Menu::saveButton);

    /**  Штука, чтобы отображались иконки */
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    /** Сочетание клавиш */
    newfile->setShortcut(tr("CTRL+N"));
    open->setShortcut(tr("CTRL+O"));
    save->setShortcut(tr("CTRL+S"));
    quit->setShortcut(tr("CTRL+Q"));
    color->setShortcut(tr("CTRL+C"));
    font->setShortcut(tr("CTRL+F"));
    wincolor->setShortcut(tr("CTRL+W"));
    about->setShortcut(tr("CTRL+A"));

    /** Панель ToolBar. Первая только рабочая, остальные  пока что для примера*/
    QToolBar *toolbar = addToolBar("Menu");
    QAction *addRectangle = toolbar->addAction(QIcon(rectanglepix), "Rectangle");
    toolbar->addAction(QIcon(colorpix), "Rectangle");
    toolbar->addAction(QIcon(helppix), "Rectangle");
    connect(addRectangle, &QAction::triggered, this, &Menu::change_state);
}

void Menu::newFileButton() {
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}

void Menu::helpButton() {
    QMessageBox::information(this, tr("About"), tr("Помощи не будет"));
}

void Menu::colorButton() {
    mcolor = QColorDialog::getColor(Qt::yellow, this);
    if (mcolor.isValid())
        qDebug() << "Color Choosen : " << mcolor.name();
    changeColor(mcolor);
}

void Menu::changeColor(QColor newColor) {
    scene.setColor(newColor);
    QPainter edit;
    edit.setBrush(QColor(newColor));
}

void Menu::fontButton() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 18), this, tr("Pick a font"));
    if (ok) {
        qDebug() << "font           : " << font;
        qDebug() << "font weight    : " << font.weight();
        qDebug() << "font family    : " << font.family();
        qDebug() << "font style     : " << font.style();
        qDebug() << "font pointSize : " << font.pointSize();
    }
}

void Menu::changeFont(QFont newFont) {
    scene.setFont(newFont);
}

void Menu::openButton() {
    /** Поставить другое расширение */
    QString str = QFileDialog::getExistingDirectory(0, "Open Dialog", "");
}

void Menu::changeWindowColor(QColor newColor) {
    scene.setWindowColor(newColor);
}

void Menu::windowColorButton() {
    wcolor = QColorDialog::getColor(Qt::white, this);
    if (wcolor.isValid())
        qDebug() << "Color Choosen : " << wcolor.name();
    changeWindowColor(wcolor);
}

void Menu::saveButton() {
    /** Заберём путь к файлу и его имененем, который будем создавать */
    QString newPath = QFileDialog::getSaveFileName(this, trUtf8("Save SVG"), path, tr("SVG files (*.svg)"));

    if (newPath.isEmpty())
        return;
    path = newPath;

    QSvgGenerator generator;

    /** Устанавливаем путь к файлу  +  размер области */
    generator.setFileName(path);
    generator.setSize(QSize(scene.width(), scene.height()));
    generator.setViewBox(QRect(0, 0, scene.width(), scene.height()));

    /** Титульное название документа + описание  */
    generator.setTitle(trUtf8("SVG Example"));
    generator.setDescription(trUtf8("File created by SVG Example"));

    QPainter painter;
    /** Устанавливаем устройство/объект в котором будем производить отрисовку */
    painter.begin(&generator);

    /** Отрисовываем содержимое сцены с помощью painter в целевое устройство/объект */
    scene.render(&painter);
    painter.end();
}

void Menu::change_state() {
    if (scene.state == SDRAW) {
        scene.state = SMOVE;
        for (auto &my_item : scene.my_items) {
            my_item->state = IMOVE;
        }
    } else {
        scene.state = SDRAW;
        for (auto &my_item : scene.my_items) {
            my_item->state = IDRAW;
        }
    }
}
