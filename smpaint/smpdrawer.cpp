#include "stdafx.h"
#include "smpdrawer.h"

SmpDrawer* SmpDrawer::instance = nullptr;

SmpDrawer::SmpDrawer(QWidget* parent) {
    setParent(parent);
}

SmpDrawer::~SmpDrawer() {
    if (shapesList.size() > 0) { qDeleteAll(shapesList); }
    if (currentShape != nullptr) { delete currentShape; }
    if (pluginsLoader != nullptr) { delete pluginsLoader; }
    delete ShapeFactory::instance();
}

SmpDrawer* SmpDrawer::getInstance() {
    if (instance == nullptr) {
        instance = new SmpDrawer();
    }
    return instance;
}

void SmpDrawer::loadPlugins() {
    pluginsLoader = new PluginsLoader(getInstance(), sideBar->getEditPluginsLayout());
    pluginsList = pluginsLoader->loadPlugins();
}

void SmpDrawer::setCurrentShape(QString shapeName) {
    if (currentShape != nullptr && !currentShape->isDrawn()) {
        delete currentShape;
    }

    currentShape = ShapeFactory::instance()->buildShape(shapeName);
    sideBar->setCurrentShape(currentShape->getName());
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void SmpDrawer::setCurrentShape(QString shapeName, const QVector<std::pair<int, shproperty>>& shapeData,
                                const QColor& borderColor) {
    if (currentShape != nullptr && !currentShape->isDrawn()) {
        delete currentShape;
    }

    currentShape = ShapeFactory::instance()->buildShape(shapeName);
    currentShape->setData(shapeData);
    currentShape->setBorderColor(borderColor);
    sideBar->setCurrentShape(currentShape->getName());
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void SmpDrawer::setCurrentShape(Shape* shape) {
    currentShape = shape;
    currentShape->setData(shape->getData());
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}

void SmpDrawer::addNewShape(Shape* shape) {
    shapesList.insert(shapesList.begin(), shape);
    sideBar->addDrawnShape(shape->getName());
    redrawShapes();
}

void SmpDrawer::addShapesList(const QVector<Shape*>& shapes) {
    shapesList = shapes;
    const QStringList shapesNames = getShapesNames();
    sideBar->addDrawnShapes(shapesNames);
    QString lastLoadedShapeName = getLastShape()->getName();
    setCurrentShape(lastLoadedShapeName);
    redrawShapes();
}

void SmpDrawer::redrawShapes() {
    drawCanvas->update();
}

void SmpDrawer::removeDrawnShape(int index) {
    Shape* removedShape = shapesList.at(index);
    delete removedShape;
    shapesList.remove(index);
    redrawShapes();
}

void SmpDrawer::removeDrawnShapes() {
    qDeleteAll(shapesList);
    shapesList.clear();
    sideBar->clearDrawnShapes();
}

const QStringList SmpDrawer::getShapesNames() {
    QStringList shapesNames;
    for (Shape* shape : shapesList) {
        shapesNames.append(shape->getName());
    }
    return shapesNames;
}

void SmpDrawer::handleShapeChange(QString newShapeName) {
    setCurrentShape(newShapeName);
}

void SmpDrawer::handleDataChange(int dataInd, int newValue) {
    currentShape->setData(dataInd, newValue);
    if (currentShape->calculatePoints()) { redrawShapes(); }
}

void SmpDrawer::handleCenterXCoordChange(int x) {
    currentShape->setCenterXCoord(x);
    if (currentShape->calculatePoints()) { redrawShapes(); }
}

void SmpDrawer::handleCenterYCoordChange(int y) {
    currentShape->setCenterYCoord(y);
    if (currentShape->calculatePoints()) { redrawShapes(); }
}

void SmpDrawer::selectDrawnShape(int index) {
    if (shapesList.isEmpty()) {
        return;
    }
    currentShape = shapesList[index];
    sideBar->createShapeDataFields(currentShape);
    sideBar->setShapeCoordinates(currentShape->getCenter());
}
