#include "stdafx.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {};

void MainWidget::setupUi(QMainWindow* SmpaintClass) {
    if (SmpaintClass->objectName().isEmpty()) {
        SmpaintClass->setObjectName("SmpaintClass");
    }
    SmpaintClass->resize(1000, 550);
    SmpaintClass->setMinimumSize(QSize(0, 0));

    scrollArea = new QScrollArea();
    createDrawCanvas(QRect(0, 0, 1000, 565), QSize(100, 50),
                     QColor(255, 255, 255, 255));
    scrollArea->setWidget(drawCanvas);
    drawCanvas->setResizable();

    createGridLayout();
}

void MainWidget::createGridLayout() {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName("gridLayout");
    gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    gridLayout->addWidget(scrollArea, 0, 1, 1, 1);
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
