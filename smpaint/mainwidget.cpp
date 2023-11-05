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

    scrollArea = new QScrollArea(this);
    createDrawCanvas(QRect(0, 0, 1000, 565), QSize(100, 50),
                     QColor(255, 255, 255, 255));
    scrollArea->setWidget(drawCanvas);
    drawCanvas->setResizable();

    createGridLayout();
    gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

    createMenuBar(SmpaintClass);
    addMenuBarSubmenu(&menuFile, "menuFile", "File", "SmpaintClass");
    addSubmenuAction(menuFile, &openAction, "openAction",
                     SmpaintClass, "SmpaintClass", "Open", "Ctrl+O");
    addSubmenuAction(menuFile, &saveAction, "saveAction",
                     SmpaintClass, "SmpaintClass", "Save", "Ctrl+S");

}

MainWidget* MainWidget::getInstance() {
    if (instance == nullptr) {
        instance = new MainWidget();
    }
    return instance;
}

void MainWidget::createGridLayout() {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    gridLayout->setColumnStretch(1, 5);
}

void MainWidget::createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                  const QColor& backgroundColor) {
    drawCanvas = new DrawCanvas();
    drawCanvas->setObjectName("drawCanvas");
    drawCanvas->setGeometry(startGeometry);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(100);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    drawCanvas->setSize(sizePolicy, minSize, QSize(0, 0));

    QPalette palette;
    QBrush brush(backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
    drawCanvas->setBackgroundColor(palette);
}

void MainWidget::createMenuBar(QMainWindow* SmpaintClass) {
    menuBar = new QMenuBar(SmpaintClass);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, SmpaintClass->width(), 22));
    SmpaintClass->setMenuBar(menuBar);
}

void MainWidget::addMenuBarSubmenu(QMenu** submenu, const char* submenuName,
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
