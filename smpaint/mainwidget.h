#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"
#include "ui/menu.h"
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
    void setCurrentShape(Shape* shape);

    Shape* getCurrentShape() { return currentShape; }
    QVector<Shape*>& getShapesList() { return shapesList; }

    void addNewShape(Shape* shape);
    void redrawShapes();
    void removeDrawnShape(int index);
    void removeDrawnShapes();
    void updateSidebar();
    void updateDrawCanvas();

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

    static MainWidget* _instance;

    SMenuBar* menuBar = nullptr;
    QGridLayout* gridLayout = nullptr;
    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    QVector<Shape*> shapesList;
    Shape* currentShape = nullptr;
};
