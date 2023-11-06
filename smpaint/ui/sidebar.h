#pragma once

#include <qwidget.h>

class SideBar : public QVBoxLayout {

    Q_OBJECT

public:
    SideBar(QWidget* parent = nullptr);

private:
    QSpacerItem* sideBarSpacer = nullptr;

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

    void createSelectArea(int spacing);
    QLabel* createLabel(QWidget* parent, const char* qtObjName,
                        const char* labelText);
    QComboBox* createCombobox(QWidget* parent, const char* qtObjName,
                              int maxWidth);

    void createCoordinatesArea(int spacing, int maxWidth);
    QSpinBox* createSpinBox(QWidget* parent, const char* qtObjName,
                            int maxWidth, int minValue, int maxValue);
    QPushButton* createPushButton(QWidget* parent, const char* qtObjName, 
                                  const char* buttonText, int maxWidth);

    void createShapeDataArea(int spacing);


};
