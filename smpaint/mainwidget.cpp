#include "stdafx.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent) {}

MainWidget::~MainWidget() {
    if (shapesList.size() > 0) { qDeleteAll(shapesList); }
    if (currentShape != nullptr) { delete currentShape; }
    delete ShapeFactory::instance();
}

MainWidget* MainWidget::_instance = nullptr;

void MainWidget::setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight) {
    if (SmpaintClass->objectName().isEmpty()) {
        SmpaintClass->setObjectName("SmpaintClass");
    }
    SmpaintClass->resize(windowWidth, windowHeight);
    SmpaintClass->setMinimumSize(QSize(0, 0));

    // Create a resizable draw canvas with scrollbars
    scrollArea = new QScrollArea(this);
    drawCanvas = createDrawCanvas(QRect(0, 0, 850, 550), QSize(100, 50),
                                  QColor(255, 255, 255, 255));
    scrollArea->setWidget(drawCanvas); 
    drawCanvas->setResizable();

    gridLayout = createGridLayout();
    gridLayout->addWidget(scrollArea, 0, 1, 1, 1);

    menuBar = new SMenuBar(this, "menuBar", SmpaintClass->width());
    SmpaintClass->setMenuBar(menuBar);

    sideBar = new SideBar(MainWidget::instance(), 20, 6, 180);
    sideBar->populateShapeCombobox(ShapeFactory::instance()->getShapesNames());
    gridLayout->addLayout(sideBar, 0, 0, 1, 1);
}

MainWidget* MainWidget::instance() {
    if (_instance == nullptr) {
        _instance = new MainWidget();
    }
    return _instance;
}

void MainWidget::setCurrentShape(QString shapeName) {
    if (currentShape != nullptr && !currentShape->isDrawn()) {
        delete currentShape;
    }

    currentShape = ShapeFactory::instance()->buildShape(shapeName);
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void MainWidget::setCurrentShape(QString shapeName, QVector<int>& shapeData) {
    if (currentShape != nullptr && !currentShape->isDrawn()) {
        delete currentShape;
    }

    currentShape = ShapeFactory::instance()->buildShape(shapeName);
    currentShape->setData(shapeData);
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void MainWidget::setCurrentShape(Shape* shape) {
    currentShape = shape;
    currentShape->setData(shape->getData());
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void MainWidget::handleShapeChange(QString newShapeName) {
    setCurrentShape(newShapeName);
}

void MainWidget::handleDataChange(int dataInd, int newValue) {
    currentShape->setData(dataInd, newValue);
}

void MainWidget::selectDrawnShape(int index) {
    if (shapesList.isEmpty()) {
        return;
    }

    currentShape = shapesList[index];
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void MainWidget::addNewShape(Shape* shape) {
    if (shape->isDrawn()) {
        drawCanvas->update();
        return;
    }

    shapesList.insert(shapesList.begin(), shape);
    sideBar->addDrawnShape(shape->getName());
    drawCanvas->update();
}

void MainWidget::removeDrawnShape(int index) {
    Shape* removedShape = shapesList.at(index);
    delete removedShape;
    shapesList.remove(index);
    drawCanvas->update();
}

void MainWidget::removeDrawnShapes() {
    qDeleteAll(shapesList);
    shapesList.clear();
    sideBar->clearDrawnShapes();
}

void MainWidget::updateSidebar() {
    sideBar->update();
}

void MainWidget::updateDrawCanvas() {
    drawCanvas->update();
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
    canvas = new DrawCanvas(MainWidget::instance(), startGeometry,
                            sizePolicy, minSize, backgroundPalette);
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
