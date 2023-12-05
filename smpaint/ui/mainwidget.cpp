#include "stdafx.h"
#include "mainwidget.h"
#include "../core/smpdrawer.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {}

void MainWidget::setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight) {
    SmpaintClass->resize(windowWidth, windowHeight);
    SmpaintClass->setMinimumSize(QSize(0, 0));
    menuBar = new SMenuBar(this, SmpaintClass->width());
    SmpaintClass->setMenuBar(menuBar);
    createGridLayout();
    createDrawCanvas(QRect(0, 0, DRAWCANV_WIDTH, DRAWCANV_HEIGHT),
                     QSize(DRAWCANV_MIN_WIDTH, DRAWCANV_HEIGHT), Qt::white);
    createSideBar();
    SmpDrawer::getInstance()->loadPlugins();
}

void MainWidget::createGridLayout() {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(CONT_MARGINS, CONT_MARGINS, CONT_MARGINS, CONT_MARGINS);
    gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 5);
}

void MainWidget::createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                  const QColor& backgroundColor) {
    QSizePolicy sizePolicy = createExpandSizePolicy(100, 0);
    QPalette backgroundPalette = createPalette(backgroundColor);
    // Create a resizable draw canvas with scrollbars
    scrollArea = new QScrollArea(this);
    drawCanvas = new DrawCanvas(this, startGeometry,
                                sizePolicy, minSize, backgroundPalette);
    scrollArea->setWidget(drawCanvas);
    drawCanvas->setResizable();
    SmpDrawer::getInstance()->registerDrawCanvas(drawCanvas);
    gridLayout->addWidget(scrollArea, 0, 1, 1, 1);
}

void MainWidget::createSideBar() {
    sideBar = new SideBar(this, SIDE_BAR_SPACING, LAYOUTS_ITEMS_SPACING, SIDE_BAR_MAX_WIDTH);
    SmpDrawer::getInstance()->registerSideBar(sideBar);
    sideBar->populateShapeCombobox(ShapeFactory::instance()->getShapesNames());
    gridLayout->addLayout(sideBar, 0, 0, 1, 1);
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
