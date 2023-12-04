#pragma once

#include "../shapes/shape.h"

class SideBar : public QVBoxLayout {

    Q_OBJECT

public:
    SideBar(QWidget* parent, int spacing,
            int itemsSpacing, int maxWidth);
    void populateShapeCombobox(const QStringList& items);
    void addDrawnShape(const QString& shapeName);
    void clearDrawnShapes();
    void createShapeDataFields(Shape* shape);
    void setCurrentShape(const QString& shapeName);
    void setShapeCoordinates(const Point& center);
    void addEditPluginUi(QWidget* label, QWidget* field);

public slots:
    void handleDeleteButtonClick();
    void handleDrawButtonClick();

private:
    void createSelectArea(int spacing);
    QLabel* createLabel(QWidget* parent, const QString labelText);
    QComboBox* createCombobox(QWidget* parent, int maxWidth);

    void createCoordinatesArea(int spacing, int maxWidth);
    QSpinBox* createSpinBox(QWidget* parent, int maxWidth,
                            int minValue, int maxValue, int defaultValue);
    QPushButton* createPushButton(QWidget* parent, const char* buttonText, int maxWidth);

    void createShapeDataArea(int spacing, int maxWidth);
    void createEditPluginsArea(int spacing, int maxWidth);

    QLabel* shapesLabel = nullptr;
    QComboBox* shapesComboBox = nullptr;
    QLabel* drawnShapesLabel = nullptr;
    QComboBox* drawnShapesComboBox = nullptr;
    QPushButton* deleteButton = nullptr;
    QFormLayout* selectLayout = nullptr;

    QLabel* xLabel = nullptr;
    QSpinBox* xSpinBox = nullptr;
    QLabel* yLabel = nullptr;
    QSpinBox* ySpinBox = nullptr;
    QFormLayout* coordLayout = nullptr;
    QGroupBox* coordGroupBox = nullptr;
    QPushButton* drawButton = nullptr;

    QFormLayout* shapeDataLayout = nullptr;
    QGroupBox* shapeDataGroupBox = nullptr;

    QFormLayout* editPluginsLayout = nullptr;
    QGroupBox* editPluginsGroupBox = nullptr;

    QSpacerItem* sideBarSpacer = nullptr;
};
