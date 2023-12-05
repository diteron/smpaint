#include "stdafx.h"
#include "../core/smpdrawer.h"
#include "sidebar.h"

SideBar::SideBar(QWidget* parent, int spacing,
                 int itemsSpacing, int maxWidth) : QVBoxLayout(parent) {
    this->setSpacing(spacing);
    createSelectArea(itemsSpacing);
    createCoordinatesArea(itemsSpacing, maxWidth);
    createShapeDataArea(itemsSpacing, maxWidth);
    createEditPluginsArea(itemsSpacing, maxWidth);
    sideBarSpacer = new QSpacerItem(SPACER_WIDTH, SPACER_HEIGHT, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->addItem(sideBarSpacer);
}

void SideBar::populateShapeCombobox(const QStringList& items) {
    shapesComboBox->addItems(items);
}

void SideBar::addDrawnShape(const QString& shapeName) {
    drawnShapesComboBox->insertItem(0, shapeName);
}

void SideBar::addDrawnShapes(const QStringList shapesNames) {
    drawnShapesComboBox->addItems(shapesNames);
}

void SideBar::clearDrawnShapes() {
    drawnShapesComboBox->clear();
}

void SideBar::setShapeCoordinates(const Point& center) {
    xSpinBox->setValue(center.x());
    ySpinBox->setValue(center.y());
}

void SideBar::setCurrentShape(const QString& shapeName) {
    shapesComboBox->setCurrentText(shapeName);
}

QFormLayout* SideBar::getEditPluginsLayout() {
    return editPluginsLayout;
}

void SideBar::addEditPluginUi(QWidget* label, QWidget* field) {
    editPluginsLayout->addRow(label, field);
}

void SideBar::createShapeDataFields(Shape* shape) {
    // Delete old rows
    if (shapeDataLayout->rowCount() > 0) {
        int rowCount = shapeDataLayout->rowCount();
        for (int i = rowCount - 1; i >= 0; --i) {
            shapeDataLayout->removeRow(i);
        }
    }

    QVector<DataField> fields = shape->getDataFields();
    QVector<std::pair<int, shproperty>> shapeData = shape->getData();
    for (unsigned i = 0; i < fields.size(); ++i) {
        QLabel* label = createLabel(this->parentWidget(), fields[i].getFieldName());
        QSpinBox* spinbox = createSpinBox(this->parentWidget(), 90, 0, 1000, shapeData[i].first);
        spinbox->connect(spinbox, &QSpinBox::valueChanged, SmpDrawer::getInstance(),
                         [=](int value) { return SmpDrawer::getInstance()->handleDataChange(i, value); } );
        shapeDataLayout->insertRow(i, label, spinbox);
    }
}

void SideBar::createSelectArea(int spacing) {
    selectLayout = new QFormLayout(this->parentWidget());
    selectLayout->setSpacing(spacing);

    shapesLabel = createLabel(this->parentWidget(), "Select shape: ");
    shapesComboBox = createCombobox(this->parentWidget(), COMBOBOX_MAX_WIDTH);
    shapesComboBox->connect(shapesComboBox, &QComboBox::currentTextChanged,
                            SmpDrawer::getInstance(), &SmpDrawer::handleShapeChange);
    shapesComboBox->connect(shapesComboBox, &QComboBox::textActivated,
                            SmpDrawer::getInstance(), &SmpDrawer::handleShapeChange);
    selectLayout->addRow(shapesLabel, shapesComboBox);

    drawnShapesLabel = createLabel(this->parentWidget(), "Drawn shapes: ");
    drawnShapesComboBox = createCombobox(this->parentWidget(), COMBOBOX_MAX_WIDTH);
    drawnShapesComboBox->connect(drawnShapesComboBox, &QComboBox::activated,
                                 SmpDrawer::getInstance(), &SmpDrawer::selectDrawnShape);
    selectLayout->addRow(drawnShapesLabel, drawnShapesComboBox);

    deleteButton = createPushButton(this->parentWidget(), "Delete shape", BUTTON_MAX_WIDTH);
    deleteButton->connect(deleteButton, &QPushButton::clicked,
                        this, &SideBar::handleDeleteButtonClick);
    selectLayout->setWidget(3, QFormLayout::FieldRole, deleteButton);

    this->addLayout(selectLayout);
}

QLabel* SideBar::createLabel(QWidget* parent, const QString labelText) {
    QLabel* label = new QLabel(parent);
    label->setText(labelText);
    return label;
}

QComboBox* SideBar::createCombobox(QWidget* parent, int maxWidth) {
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->setMaximumSize(QSize(maxWidth, COMBOBOX_MAX_HEIGHT));
    return comboBox;
}

void SideBar::createCoordinatesArea(int spacing, int maxWidth) {
    coordGroupBox = new QGroupBox("Coordinates", this->parentWidget());
    coordGroupBox->setMaximumSize(QSize(maxWidth, GROUPBOX_MAX_HEIGHT));

    coordLayout = new QFormLayout(this->parentWidget());
    coordLayout->setSpacing(spacing);

    xLabel = createLabel(this->parentWidget(), "x:     ");
    xSpinBox = createSpinBox(this->parentWidget(), SPINBOX_MAX_WIDTH, 0, 1000, 0);
    xSpinBox->connect(xSpinBox, &QSpinBox::valueChanged, SmpDrawer::getInstance(),
                     &SmpDrawer::handleCenterXCoordChange);
    coordLayout->addRow(xLabel, xSpinBox);
    yLabel = createLabel(this->parentWidget(), "y:     ");
    ySpinBox = createSpinBox(this->parentWidget(), SPINBOX_MAX_WIDTH, 0, 1000, 0);
    ySpinBox->connect(ySpinBox, &QSpinBox::valueChanged, SmpDrawer::getInstance(),
                      &SmpDrawer::handleCenterYCoordChange);
    coordLayout->addRow(yLabel, ySpinBox);

    drawButton = createPushButton(this->parentWidget(), "Draw", BUTTON_MAX_WIDTH);
    drawButton->connect(drawButton, &QPushButton::clicked,
                        this, &SideBar::handleDrawButtonClick);
    coordLayout->setWidget(3, QFormLayout::FieldRole, drawButton);

    coordGroupBox->setLayout(coordLayout);
    this->addLayout(coordLayout);
    this->addWidget(coordGroupBox);
}

void SideBar::handleDeleteButtonClick() {
    int drawnShapeIndex = drawnShapesComboBox->currentIndex();
    if (drawnShapeIndex == -1) { return; }      // If the combobox is empty, there is nothing to remove

    drawnShapesComboBox->removeItem(drawnShapeIndex);
    SmpDrawer::getInstance()->removeDrawnShape(drawnShapeIndex);
    
    QString newShapeToDraw = shapesComboBox->currentText();
    SmpDrawer::getInstance()->setCurrentShape(newShapeToDraw);
}

void SideBar::handleDrawButtonClick() {
    Shape* drawingShape = SmpDrawer::getInstance()->getCurrentShape();
    Point center(xSpinBox->value(), ySpinBox->value());
    drawingShape->setCenter(center);
    if (drawingShape->calculatePoints()) {
        if (!drawingShape->isDrawn()) {
            SmpDrawer::getInstance()->addNewShape(drawingShape);
            drawingShape->setDrawn();
        }

        Shape* lastShape = SmpDrawer::getInstance()->getLastShape();
        SmpDrawer::getInstance()->setCurrentShape(lastShape->getName(),           // Create a new current shape
                                                lastShape->getData(),           // with data from the last drawn shape
                                                lastShape->getBorderColor());
    }
}

QSpinBox* SideBar::createSpinBox(QWidget* parent, int maxWidth,
                                 int minValue, int maxValue, int defaultValue) {
    QSpinBox* spinBox = new QSpinBox(parent);
    spinBox->setMaximumSize(QSize(maxWidth, SPINBOX_MAX_HEIGHT));
    spinBox->setRange(minValue, maxValue);
    spinBox->setValue(defaultValue);
    return spinBox;
}

QPushButton* SideBar::createPushButton(QWidget* parent, const char* buttonText, int maxWidth) {
    QPushButton* pushButton = new QPushButton(buttonText, parent);
    pushButton->setMaximumSize(QSize(maxWidth, BUTTON_MAX_HEIGHT));
    return pushButton;
}

void SideBar::createShapeDataArea(int spacing, int maxWidth) {
    shapeDataGroupBox = new QGroupBox("Shape Data", this->parentWidget());
    shapeDataGroupBox->setMaximumSize(QSize(maxWidth, GROUPBOX_MAX_HEIGHT));

    shapeDataLayout = new QFormLayout(this->parentWidget());
    shapeDataLayout->setSpacing(spacing);

    shapeDataGroupBox->setLayout(shapeDataLayout);
    this->addLayout(shapeDataLayout);
    this->addWidget(shapeDataGroupBox);
}

void SideBar::createEditPluginsArea(int spacing, int maxWidth) {
    editPluginsGroupBox = new QGroupBox("Edit shape", this->parentWidget());
    editPluginsGroupBox->setMaximumSize(QSize(maxWidth, GROUPBOX_MAX_HEIGHT));

    editPluginsLayout = new QFormLayout(this->parentWidget());
    editPluginsLayout->setSpacing(spacing);

    editPluginsGroupBox->setLayout(editPluginsLayout);
    this->addLayout(editPluginsLayout);
    this->addWidget(editPluginsGroupBox);
}
