#pragma once

#include <qwidget.h>
#include "../shapes/shape.h"

class SideBar : public QVBoxLayout {

    Q_OBJECT

public:
    SideBar(QWidget* parent, int spacing,
            int itemsSpacing, int maxWidth);
    void populateShapeCombobox(const QStringList& items);
    void addDrawnShape(const QString& shapeName);
    void removeDrawnShape(int index);
    void createShapeDataFields(Shape* shape);

private:
    void createSelectArea(int spacing);
    QLabel* createLabel(QWidget* parent, const std::string qtObjName,
                        const QString labelText);
    QComboBox* createCombobox(QWidget* parent, const char* qtObjName,
                              int maxWidth);

    void createCoordinatesArea(int spacing, int maxWidth);
    QSpinBox* createSpinBox(QWidget* parent, const std::string qtObjName,
                            int maxWidth, int minValue, int maxValue, int defaultValue);
    QPushButton* createPushButton(QWidget* parent, const char* qtObjName,
                                  const char* buttonText, int maxWidth);

    void createShapeDataArea(int spacing, int maxWidth);

    QLabel* shapesLabel = nullptr;
    QComboBox* shapesComboBox = nullptr;
    QLabel* drawnShapesLabel = nullptr;
    QComboBox* drawnShapesComboBox = nullptr;
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
    QSpacerItem* sideBarSpacer = nullptr;
};
