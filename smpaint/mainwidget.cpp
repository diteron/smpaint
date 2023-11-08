#include "stdafx.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {};

MainWidget* MainWidget::instance = nullptr;

void MainWidget::setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight) {
    if (SmpaintClass->objectName().isEmpty()) {
        SmpaintClass->setObjectName("SmpaintClass");
    }
    SmpaintClass->resize(windowWidth, windowHeight);
    SmpaintClass->setMinimumSize(QSize(0, 0));

    // Create a resizable draw canvas with scrollbars
    scrollArea = new QScrollArea(this);
    drawCanvas = createDrawCanvas(QRect(0, 0, 1000, 565), QSize(100, 50),
                                  QColor(255, 255, 255, 255));
    scrollArea->setWidget(drawCanvas); 
    drawCanvas->setResizable();

    gridLayout = createGridLayout();
    gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

    menuBar = createMenuBar(SmpaintClass);
    addMenuBarSubmenu(menuBar, &menuFile, "menuFile", "File", "SmpaintClass");
    addSubmenuAction(menuFile, &openAction, "openAction",
                     SmpaintClass, "SmpaintClass", "Open", "Ctrl+O");
    addSubmenuAction(menuFile, &saveAction, "saveAction",
                     SmpaintClass, "SmpaintClass", "Save", "Ctrl+S");

    sideBar = new SideBar(getMainWidget());
    gridLayout->addLayout(sideBar, 0, 0, 1, 1);
}

MainWidget* MainWidget::getMainWidget() {
    if (instance == nullptr) {
        instance = new MainWidget();
    }
    return instance;
}

QGridLayout* MainWidget::createGridLayout() {
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(6);
    layout->setContentsMargins(11, 11, 11, 11);
    layout->setObjectName("gridLayout");
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 5);
    return layout;
}

DrawCanvas* MainWidget::createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                         const QColor& backgroundColor) {
    DrawCanvas* canvas;
    QSizePolicy sizePolicy = createExpandSizePolicy(100, 0);
    QPalette backgroundPalette = createPalette(backgroundColor);
    canvas = new DrawCanvas(getMainWidget(), startGeometry, sizePolicy, minSize, backgroundPalette);
    return canvas;
}

QSizePolicy MainWidget::createExpandSizePolicy(int horizontalStretch, int verticalStretch) {
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(horizontalStretch);
    sizePolicy.setVerticalStretch(verticalStretch);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    return sizePolicy;
}

QPalette MainWidget::createPalette(const QColor& backgroundColor) {
    QPalette palette;
    QBrush brush(backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
    return palette;
}

QMenuBar* MainWidget::createMenuBar(QMainWindow* SmpaintClass) {
    QMenuBar* menu = new QMenuBar(SmpaintClass);
    menu->setObjectName("menuBar");
    menu->setGeometry(QRect(0, 0, SmpaintClass->width(), 22));
    SmpaintClass->setMenuBar(menu);
    return menu;
}

void MainWidget::addMenuBarSubmenu(QMenuBar* menuBar, QMenu** submenu, const char* submenuName,
                                   const char* title, const char* parentName) {
    *submenu = new QMenu(menuBar);
    (*submenu)->setObjectName(submenuName);
    menuBar->addAction((*submenu)->menuAction());
    (*submenu)->setTitle(QCoreApplication::translate(parentName, title, nullptr));
}

void MainWidget::addSubmenuAction(QMenu* submenu, QAction** action, const char* actionName,
                                  QWidget* parent, const char* parentName,
                                  const char* title, const char* shortcut) {
    (*action) = new QAction(parent);
    (*action)->setObjectName(actionName);
    submenu->addAction(*action);
    (*action)->setText(QCoreApplication::translate(parentName, title, nullptr));
    (*action)->setShortcut(QCoreApplication::translate(parentName, shortcut, nullptr));
}
