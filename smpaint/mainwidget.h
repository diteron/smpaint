#pragma once

#include "ui/drawcanvas.h"
#include "ui/sidebar.h"
#include "ui/menu.h"
#include "shapes/shape.h"
#include "shapes/shapefactory.h"
#include "plugins/ismpplugin.h"

class MainWidget : public QWidget {

    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();
    static MainWidget* instance();

    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);
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
    void redrawShapes();
    void removeDrawnShape(int index);
    void removeDrawnShapes();
    void updateSidebar();
    void updateDrawCanvas();

public slots:
    void handleShapeChange(QString newShapeName);
    void handleDataChange(int dataInd, int newValue);
    void handleCenterXCoordChange(int x);
    void handleCenterYCoordChange(int y);
    void selectDrawnShape(int index);

private:
    QGridLayout* createGridLayout();
    void loadPlugins();
    void addPluginUi(QObject* plugin);
    DrawCanvas* createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                 const QColor& backgroundColor);
    QSizePolicy createExpandSizePolicy(int horizontalStretch, int verticalStretch);
    QPalette createPalette(const QColor& backgroundColor);

    static MainWidget* _instance;

    SMenuBar* menuBar = nullptr;
    QGridLayout* gridLayout = nullptr;
    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    QVector<Shape*> shapesList;
    Shape* currentShape = nullptr;

    ISmpPlugin* currentPlugin = nullptr;
    QVector<ISmpPlugin*> pluginsList;
};
