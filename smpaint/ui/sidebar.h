#pragma once

#include "../shapes/shape.h"

class SideBar : public QVBoxLayout {

    Q_OBJECT

public:
    SideBar(QWidget* parent, int spacing,
            int itemsSpacing, int maxWidth);
    void populateShapeCombobox(const QStringList& items);
    void addDrawnShape(const QString& shapeName);
    void addDrawnShapes(const QStringList shapesNames);
    void clearDrawnShapes();
    void createShapeDataFields(Shape* shape);
    void setCurrentShape(const QString& shapeName);
    void setShapeCoordinates(const Point& center);
    QFormLayout* getEditPluginsLayout();
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

    const int SPACER_WIDTH = 20;
    const int SPACER_HEIGHT = 40;
    const int COMBOBOX_MAX_WIDTH = 120;
    const int BUTTON_MAX_WIDTH = 90;
    const int SPINBOX_MAX_WIDTH = 90;
    const int COMBOBOX_MAX_HEIGHT = 40;
    const int BUTTON_MAX_HEIGHT = 40;
    const int SPINBOX_MAX_HEIGHT = 40;
    const int GROUPBOX_MAX_HEIGHT = 16777215;
};
