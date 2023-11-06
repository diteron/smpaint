#include "stdafx.h"
#include "sidebar.h"

SideBar::SideBar(QWidget* parent) : QVBoxLayout(parent) {
    this->setSpacing(20);
    this->setObjectName("SideBar");
    createSelectArea(6);
    createCoordinatesArea(6, 180);
    sideBarSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->addItem(sideBarSpacer);
}

void SideBar::createSelectArea(int spacing) {
    selectLayout = new QFormLayout();
    selectLayout->setSpacing(spacing);
    selectLayout->setObjectName("selectLayout");

    shapesLabel = createLabel(parentWidget(), "shapesLabel", "Select shape: ");
    shapesComboBox = createCombobox(parentWidget(), "shapesComboBox", 120);
    selectLayout->addRow(shapesLabel, shapesComboBox);
    drawnShapesLabel = createLabel(parentWidget(), "drawnShapesLabel", "Drawn shapes: ");
    drawnShapesComboBox = createCombobox(parentWidget(), "drawnShapesComboBox", 120);
    selectLayout->addRow(drawnShapesLabel, drawnShapesComboBox);

    this->addLayout(selectLayout);
}

QLabel* SideBar::createLabel(QWidget* parent, const char* qtObjName,
                             const char* labelText) {
    QLabel* label = new QLabel(parent);
    label->setObjectName(qtObjName);
    label->setText(QCoreApplication::translate("SideBar", labelText, nullptr));
    return label;
}

QComboBox* SideBar::createCombobox(QWidget* parent, const char* qtObjName,
                                 int maxWidth) {
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->setObjectName(qtObjName);
    comboBox->setMaximumSize(QSize(maxWidth, 16777215));
    return comboBox;
}

void SideBar::createCoordinatesArea(int spacing, int maxWidth) {
    coordGroupBox = new QGroupBox("Coordinates");
    coordGroupBox->setMaximumSize(QSize(maxWidth, 16777215));

    coordLayout = new QFormLayout();
    coordLayout->setSpacing(spacing);
    coordLayout->setObjectName("coordLayout");

    xLabel = createLabel(parentWidget(), "xLabel", "x:     ");
    xSpinBox = createSpinBox(parentWidget(), "xSpinBox", 90, 0, 1000);
    coordLayout->addRow(xLabel, xSpinBox);
    yLabel = createLabel(parentWidget(), "yLabel", "y:     ");
    ySpinBox = createSpinBox(parentWidget(), "ySpinBox", 90, 0, 1000);
    coordLayout->addRow(yLabel, ySpinBox);

    drawButton = createPushButton(parentWidget(), "drawButton", "Draw", 90);
    coordLayout->setWidget(3, QFormLayout::FieldRole, drawButton);

    coordGroupBox->setLayout(coordLayout);
    this->addLayout(coordLayout);
    this->addWidget(coordGroupBox);
}

QSpinBox* SideBar::createSpinBox(QWidget* parent, const char* qtObjName,
                                 int maxWidth, int minValue, int maxValue) {
    QSpinBox* spinBox = new QSpinBox(parent);
    spinBox->setObjectName(qtObjName);
    spinBox->setMaximumSize(QSize(maxWidth, 16777215));
    spinBox->setRange(minValue, maxValue);
    return spinBox;
}

QPushButton* SideBar::createPushButton(QWidget* parent, const char* qtObjName,
                                       const char* buttonText, int maxWidth) {
    QPushButton* pushButton = new QPushButton(buttonText, parent);
    pushButton->setObjectName(qtObjName);
    pushButton->setMaximumSize(QSize(maxWidth, 16777215));
    return pushButton;
}
