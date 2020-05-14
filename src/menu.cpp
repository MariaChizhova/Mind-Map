#include "menu.h"
#include "svgreader.h"
#include "svgsaver.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent) {
    /** Добавление иконок. Пропишите свой путь к иконкам */
    QPixmap newpix(":/icons/new.png");
    QPixmap savepix(":/icons/save.png");
    QPixmap quitpix(":/icons/quit.png");
    QPixmap helppix(":/icons/help.png");
    QPixmap colorpix(":/icons/color.png");
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
    QAction *linecolor = new QAction(wincolorpix, "&LineColor", this);

    /** Создаём объект класса QMenu (меню) */
    QMenu *file = menuBar()->addMenu("&File");
    QMenu *edit = menuBar()->addMenu("&Edit");
    QMenu *help = menuBar()->addMenu("&Help");

    /** Помещаем действие в меню с помощью метода addAction() */
    file->addAction(newfile);
    file->addAction(open);
    file->addAction(save);
    file->addAction(quit);
    help->addAction(about);
    edit->addAction(color);
    edit->addAction(wincolor);
    edit->addAction(linecolor);

    /** Когда мы выбираем в меню опцию "Quit", то приложение сразу же завершает своё выполнение */
    connect(quit, &QAction::triggered, this, QApplication::quit);
    connect(about, &QAction::triggered, this, &Menu::helpButton);
    connect(color, &QAction::triggered, this, &Menu::colorButton);
    connect(wincolor, &QAction::triggered, this, &Menu::windowColorButton);
    connect(newfile, &QAction::triggered, this, &Menu::newFileButton);
    connect(open, &QAction::triggered, this, &Menu::openButton);
    connect(save, &QAction::triggered, this, &Menu::saveButton);
    connect(linecolor, &QAction::triggered, this, &Menu::lineColorButton);

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

    /** Панель ToolBar*/
    QToolBar *toolbar = addToolBar("Menu");
    QAction *addRectangle = toolbar->addAction(QIcon(rectanglepix), "Rectangle");
    connect(addRectangle, &QAction::triggered, this, &Menu::changeState);

    QAction *text = toolbar->addAction(QIcon(textpix), "Text");
    connect(text, &QAction::triggered, this, &Menu::enterText);

    QAction *line = toolbar->addAction("Line");
    connect(line, &QAction::triggered, this, &Menu::addLine);

    QAction *pix = toolbar->addAction("Pix");
    connect(pix, &QAction::triggered, this, &Menu::addImage);

    QPixmap exp(":/icons/rectangle-png.png");
    QPixmap exp1(":/icons/exp1.png");
    QPixmap exp2(":/icons/exp2.png");
    QPixmap exp3(":/icons/exp3.png");
    QToolBar *lefttoolbar = addToolBar("Cells");
    this->addToolBar(Qt::LeftToolBarArea, lefttoolbar);
    lefttoolbar->setFixedWidth(70);
    lefttoolbar->setIconSize(QSize(70, 70));
    QAction *rect = lefttoolbar->addAction(QIcon(exp), "Rectangle");
    connect(rect, &QAction::triggered, this, &Menu::setCellsPix);
    QAction *rect1 = lefttoolbar->addAction(QIcon(exp1), "Rectangle");
    connect(rect1, &QAction::triggered, this, &Menu::setCellsPix1);
    QAction *rect2 = lefttoolbar->addAction(QIcon(exp2), "Rectangle");
    connect(rect2, &QAction::triggered, this, &Menu::setCellsPix2);
    QAction *rect3 = lefttoolbar->addAction(QIcon(exp3), "Rectangle");
    connect(rect3, &QAction::triggered, this, &Menu::setCellsPix3);
}


void Menu::newScene() {
    scene.clear();
    changeWindowColor(Qt::white);
    bool ok;
    qreal width = QGuiApplication::primaryScreen()->size().width();
   // QString width = "1920"; // QInputDialog::getText(this, tr("Width"), tr("Enter:"), QLineEdit::Normal, "", &ok);
  //  QString height = "1080"; //QInputDialog::getText(this, tr("Height"), tr("Enter:"), QLineEdit::Normal, "", &ok);
    qreal height = QGuiApplication::primaryScreen()->size().height();
    qDebug() << "ScreenSize.width           : " << QGuiApplication::primaryScreen()->size().width();
    qDebug() << "ScreenSize.height          : " << QGuiApplication::primaryScreen()->size().height();
    if (ok && width && height)
        scene.setSceneRect(0, 0, width, height);
    /** Добавляем сцену в основное окно */
    view.setScene(&scene);
    setCentralWidget(&view);
}

void Menu::newFileButton() {
    newScene();
}

void Menu::helpButton() {
    QMessageBox::information(this, tr("About"), tr("Помощи не будет!"));
}

void Menu::colorButton() {
    mcolor = QColorDialog::getColor(Qt::yellow, this);
    if (mcolor.isValid())
        qDebug() << "Color Chosen : " << mcolor.name();
    changeColor(mcolor);
}

void Menu::changeColor(const QColor &newColor) {
    scene.setColor(newColor);
    QPainter edit;
    edit.setBrush(QColor(newColor));
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
    SvgSaver::save(&scene, path, scene.width(), scene.height());
}

void Menu::changeState() {
    if (scene.state == SDRAW) {
        scene.state = SMOVE;
        for (auto &my_item : scene.myItems) {
            if (!my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, true);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
    } else {
        scene.state = SDRAW;
        for (auto &my_item : scene.myItems) {
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
                my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
            if (my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
                my_item->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
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
            QGraphicsItemGroup *group = scene.createItemGroup({});
            group->addToGroup(rect);
            group->setHandlesChildEvents(true);
            group->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene.myItems.emplace_back(group);
            scene.addItem(rect);
        }
}

void Menu::enterText() {
    for (auto &my_item : scene.myItems) {
        if (!my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
            my_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
            my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    scene.state = STEXT;
}

void Menu::addLine() {
    for (auto &my_item : scene.myItems) {
        if (!my_item->flags().testFlag(QGraphicsItem::ItemIsSelectable))
            my_item->setFlag(QGraphicsItem::ItemIsSelectable, true);
        if (my_item->flags().testFlag(QGraphicsItem::ItemIsMovable))
            my_item->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    scene.state = SLINE;
}

void Menu::addImage() {
    scene.clear();
    QPixmap pixmap(":/icons/hruu.jpg");
    scene.setBackgroundBrush(pixmap);
}

void Menu::setCellsPix() {
    scene.pixstate = PIX;
}
void Menu::setCellsPix1() {
    scene.pixstate = PIX1;
}

void Menu::setCellsPix2() {
    scene.pixstate = PIX2;
}

void Menu::setCellsPix3() {
    scene.pixstate = PIX3;
}

void Menu::lineColorButton() {
    lcolor = QColorDialog::getColor(Qt::white, this);
    if (lcolor.isValid())
        qDebug() << "Color Choosen : " << lcolor.name();
    changeLineColor(lcolor);
}

void Menu::changeLineColor(const QColor &newColor) {
    scene.setLineColor(newColor);
}

