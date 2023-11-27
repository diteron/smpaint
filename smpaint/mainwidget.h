#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"
#include "shapes/shape.h"
#include "shapes/shapefactory.h"

class MainWidget : public QWidget {

    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    ~MainWidget();
    static MainWidget* instance();

    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);
    void setCurrentShape(QString shapeName);
    void setCurrentShape(QString shapeName, QVector<int>& shapeData);

    Shape* getCurrentShape() { return currentShape; }
    QVector<Shape*>& getShapesList() { return shapesList; }

    void addNewShape(Shape* shape);
    void removeDrawnShape(int index);
    void updateSidebar();

public slots:
    void handleShapeChange(QString newShapeName);
    void handleDataChange(int dataInd, int newValue);
    void selectDrawnShape(int index);

private:
    QGridLayout* createGridLayout();
    DrawCanvas* createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                                 const QColor& backgroundColor);
    QSizePolicy createExpandSizePolicy(int horizontalStretch, int verticalStretch);
    QPalette createPalette(const QColor& backgroundColor);
    QMenuBar* createMenuBar(QMainWindow* SmpaintClass);
    void addMenuBarSubmenu(QMenuBar* menuBar, QMenu** submenu,
                           const char* submenuName, const char* title);
    void addSubmenuAction(QMenu* submenu, QAction** action, const char* actionName,
                          QWidget* parent, const char* title, const char* shortcut);

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
};

