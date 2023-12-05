#pragma once

#include "../ui/drawcanvas.h"
#include "../ui/sidebar.h"
#include "../shapes/shapefactory.h"
#include "../plugins/pluginloader.h"
#include "../plugins/ismpplugin.h"

class SmpDrawer : public QObject {

    Q_OBJECT

public:
    SmpDrawer(QWidget* parent = nullptr);
    ~SmpDrawer();
    static SmpDrawer* getInstance();

    void registerDrawCanvas(DrawCanvas* drcanv) { drawCanvas = drcanv; };
    void registerSideBar(SideBar* sidebar) { sideBar = sidebar; };
    void loadPlugins();

    void setCurrentShape(QString shapeName);
    void setCurrentShape(QString shapeName, const QVector<std::pair<int, shproperty>>& shapeData,
                         const QColor& borderColor);
    void setCurrentShape(Shape* shape);
    void setCurrentPlugin(ISmpPlugin* plugin) { currentPlugin = plugin; }
    Shape* getCurrentShape() { return currentShape; }
    Shape* getLastShape() { return shapesList.first(); }     // New shapes are adding to the beginning of the shapes list, so the first is the last
    QVector<Shape*>& getShapesList() { return shapesList; }
    ISmpPlugin* getCurrentPlugin() { return currentPlugin; }

    void addNewShape(Shape* shape);
    void addShapesList(const QVector<Shape*>& shapes);
    void redrawShapes();
    void removeDrawnShape(int index);
    void removeDrawnShapes();

private:
    const QStringList getShapesNames();

    static SmpDrawer* instance;
    Shape* currentShape = nullptr;
    QVector<Shape*> shapesList;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    PluginsLoader* pluginsLoader = nullptr;
    ISmpPlugin* currentPlugin = nullptr;
    QVector<ISmpPlugin*> pluginsList;

public slots:
    void handleShapeChange(QString newShapeName);
    void handleDataChange(int dataInd, int newValue);
    void handleCenterXCoordChange(int x);
    void handleCenterYCoordChange(int y);
    void selectDrawnShape(int index);
};
