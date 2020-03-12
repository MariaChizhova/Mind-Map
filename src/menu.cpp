#include "menu.h"
#include "svgreader.h"

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
    QPixmap textpix(":/icons/text.png");

    /** Создаём объект класса QAction (действие) с названием пункта меню "Quit" */
    QAction *newfile = new QAction(newpix, "&New", this);
    QAction *open = new QAction(openpix, "&Open", this);
    QAction *save = new QAction(savepix, "&Save", this);
    QAction *quit = new QAction(quitpix, "&Quit", this);
    QAction *about = new QAction(helppix, "&About", this);
    QAction *color = new QAction(colorpix, "&Color", this);
    QAction *wincolor = new QAction(wincolorpix, "&WinColor", this);

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
    edit->addAction(wincolor);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, this, QApplication::quit);
    connect(about, &QAction::triggered, this, &Menu::helpButton);
    connect(color, &QAction::triggered, this, &Menu::colorButton);
    connect(wincolor, &QAction::triggered, this, &Menu::windowColorButton);
    connect(newfile, &QAction::triggered, this, &Menu::newFileButton);
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
    wincolor->setShortcut(tr("CTRL+W"));
    about->setShortcut(tr("CTRL+A"));

    /** Панель ToolBar. Первая только рабочая, остальные  пока что для примера*/
    QToolBar *toolbar = addToolBar("Menu");
    QAction *addRectangle = toolbar->addAction(QIcon(rectanglepix), "Rectangle");
    connect(addRectangle, &QAction::triggered, this, &Menu::changeState);

    QAction *text = toolbar->addAction(QIcon(textpix), "Text");
    connect(text, &QAction::triggered, this, &Menu::enterText);
}

void Menu::newScene() {
    scene.clear();
    changeWindowColor(Qt::white);
    bool ok;
    QString width = QInputDialog::getText(this, tr("Width"), tr("Enter:"),
                                         QLineEdit::Normal, "", &ok);
    QString height = QInputDialog::getText(this, tr("Height"), tr("Enter:"),
                                         QLineEdit::Normal, "", &ok);
    if (ok && !width.isEmpty() && !height.isEmpty())
        scene.setSceneRect(0, 0, width.toInt(), height.toInt());
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}

void Menu::newFileButton() {
    newScene();
}

void Menu::helpButton() {
    QMessageBox::information(this, tr("About"), tr("Пошел нахуй"));
}

void Menu::colorButton() {
    mcolor = QColorDialog::getColor(Qt::yellow, this);
    if (mcolor.isValid())
        qDebug() << "Color Choosen : " << mcolor.name();
    changeColor(mcolor);
}

void Menu::changeColor(const QColor &newColor) {
    scene.setColor(newColor);
    QPainter edit;
    edit.setBrush(QColor(newColor));
}

void Menu::changeFont(const QFont &newFont) {
    scene.setFont(newFont);
}

void Menu::changeWindowColor(const QColor &newColor) {
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

void Menu::changeState() {
    if (scene.state == SDRAW) {
        scene.state = SMOVE;
        for (auto &my_item : scene.myItems) {
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, 1);
        }
    } else {
        scene.state = SDRAW;
        for (auto &my_item : scene.myItems)
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, 0);
    }
}

void Menu::openButton() {
    scene.clear();
    changeWindowColor(Qt::white);
    view.setScene(&scene);
    setCentralWidget(&view);
    QString newPath = QFileDialog::getOpenFileName(this, trUtf8("Open SVG"), path, tr("SVG files (*.svg)"));
    if (newPath.isEmpty())
        return;

    path = newPath;
    scene.clear();

    /** Зададим размеры графической сцены */
    scene.setSceneRect(SvgReader::getSizes(path));

    /** TODO: Вставить цвет из Svgreader */
    scene.setWindowColor("#c7c7fa");

    /** Установим на графическую сцену объекты, получив их с помощью метода getElements */
            foreach (QGraphicsRectItem *item, SvgReader::getElements(path)) {
            QGraphicsRectItem *rect = item;
            scene.myItems.emplace_back(rect);
            scene.addItem(rect);
        }
}

void Menu::changeFontColor(const QColor &newColor) {
    scene.setFontColor(newColor);
}

void Menu::enterText() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Arial", 18), this, tr("Pick a font"));
    if (ok) {
        qDebug() << "font           : " << font;
        qDebug() << "font weight    : " << font.weight();
        qDebug() << "font family    : " << font.family();
        qDebug() << "font style     : " << font.style();
        qDebug() << "font pointSize : " << font.pointSize();
    }
    changeFont(font);
    scene.state = TEXT;
    fcolor = QColorDialog::getColor(Qt::black, this);
    if (fcolor.isValid())
        qDebug() << "Color Choosen : " << fcolor.name();
    changeFontColor(fcolor);
    QString text = QInputDialog::getText(this, tr("Text"), tr("Enter:"),
            QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty())
        scene.setText(text);
    scene.printText();

}