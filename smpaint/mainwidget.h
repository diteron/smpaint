#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"
#include "shapes/shapes.h"
#include "shapes/shapefactory.h"

class MainWidget : public QWidget {

    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();
    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);
    static MainWidget* instance();

    void setCurrentShape(QString shapeName);
    void selectDrawnShape(int index);
    Shape* getCurrentShape() { return currentShape; }
    QVector<Shape*>& getShapesList() { return shapesList; }
    void handleDataChange(int dataInd, int newValue);
    //void setShapePoints(std::vector<Point> points);
    void addNewShape(Shape* shape);
    void updateSidebar();
    //const std::vector<Point>& getShapePoints() { return shapePoints; }
    //const std::vector<int>& getShapeData() { return shapeData; }

private:
    static MainWidget* _instance;

    QMenuBar* menuBar = nullptr;
    QMenu* menuFile = nullptr;
    QAction* openAction = nullptr;
    QAction* saveAction = nullptr;

    QGridLayout* gridLayout = nullptr;
    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    QVector<Shape*> shapesList;
    Shape* currentShape = nullptr;
    QVector<int> shapeData;
    //std::vector<Point> shapePoints;

    QGridLayout* createGridLayout();
    DrawCanvas* createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                 const QColor& backgroundColor);
    QSizePolicy createExpandSizePolicy(int horizontalStretch, int verticalStretch);
    QPalette createPalette(const QColor& backgroundColor);
    QMenuBar* createMenuBar(QMainWindow* SmpaintClass);
    void addMenuBarSubmenu(QMenuBar* menuBar, QMenu** submenu, const char* submenuName,
                           const char* title, const char* parentName);
    void addSubmenuAction(QMenu* submenu, QAction** action, const char* actionName,
                          QWidget* parent, const char* parentName,
                          const char* title, const char* shortcut);
};

