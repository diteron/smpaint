#include "stdafx.h"
#include "../mainwidget.h"
#include "sidebar.h"

SideBar::SideBar(QWidget* parent, int spacing,
                 int itemsSpacing, int maxWidth) : QVBoxLayout(parent) {
    this->setSpacing(spacing);
    this->setObjectName("SideBar");
    createSelectArea(itemsSpacing);
    createCoordinatesArea(itemsSpacing, maxWidth);
    createShapeDataArea(itemsSpacing, maxWidth);
    sideBarSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->addItem(sideBarSpacer);
}

void SideBar::populateShapeCombobox(const QStringList& items) {
    shapesComboBox->addItems(items);
}

void SideBar::addDrawnShape(const QString& shapeName) {
    drawnShapesComboBox->insertItem(0, shapeName);
    drawnShapesComboBox->setCurrentIndex(0);
}

void SideBar::clearDrawnShapes() {
    drawnShapesComboBox->clear();
}

void SideBar::setShapeCoordinates(const Point& center) {
    xSpinBox->setValue(center.x());
    ySpinBox->setValue(center.y());
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
    QVector<int> shapeData = shape->getData();
    for (unsigned i = 0; i < fields.size(); ++i) {
        QLabel* label = createLabel(this->parentWidget(), "Field " + std::to_string(i), fields[i].getFieldName());
        QSpinBox* spinbox = createSpinBox(this->parentWidget(), "SpinBox " + std::to_string(i),
                                          90, 0, 1000, shapeData[i]);
        spinbox->connect(spinbox, &QSpinBox::valueChanged, MainWidget::instance(),
                         [=](int value) { return shape->setData(i, value); } );
        shapeDataLayout->insertRow(i, label, spinbox);
    }
}

void SideBar::createSelectArea(int spacing) {
    selectLayout = new QFormLayout(this->parentWidget());
    selectLayout->setSpacing(spacing);
    selectLayout->setObjectName("selectLayout");

    shapesLabel = createLabel(this->parentWidget(), "shapesLabel", "Select shape: ");
    shapesComboBox = createCombobox(this->parentWidget(), "shapesComboBox", 120);
    shapesComboBox->connect(shapesComboBox, &QComboBox::currentTextChanged,
                            MainWidget::instance(), &MainWidget::handleShapeChange);
    shapesComboBox->connect(shapesComboBox, &QComboBox::textActivated,
                            MainWidget::instance(), &MainWidget::handleShapeChange);
    selectLayout->addRow(shapesLabel, shapesComboBox);

    drawnShapesLabel = createLabel(this->parentWidget(), "drawnShapesLabel", "Drawn shapes: ");
    drawnShapesComboBox = createCombobox(this->parentWidget(), "drawnShapesComboBox", 120);
    drawnShapesComboBox->connect(drawnShapesComboBox, &QComboBox::activated,
                                 MainWidget::instance(), &MainWidget::selectDrawnShape);
    selectLayout->addRow(drawnShapesLabel, drawnShapesComboBox);

    deleteButton = createPushButton(this->parentWidget(), "deleteButton", "Delete shape", 90);
    deleteButton->connect(deleteButton, &QPushButton::clicked,
                        this, &SideBar::handleDeleteButtonClick);
    selectLayout->setWidget(3, QFormLayout::FieldRole, deleteButton);

    this->addLayout(selectLayout);
}

QLabel* SideBar::createLabel(QWidget* parent, const std::string qtObjName,
                             const QString labelText) {
    QLabel* label = new QLabel(parent);
    label->setObjectName(qtObjName);
    label->setText(labelText);
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
    coordGroupBox = new QGroupBox("Coordinates", this->parentWidget());
    coordGroupBox->setMaximumSize(QSize(maxWidth, 16777215));

    coordLayout = new QFormLayout(this->parentWidget());
    coordLayout->setSpacing(spacing);
    coordLayout->setObjectName("coordLayout");

    xLabel = createLabel(this->parentWidget(), "xLabel", "x:     ");
    xSpinBox = createSpinBox(this->parentWidget(), "xSpinBox", 90, 0, 1000, 0);
    coordLayout->addRow(xLabel, xSpinBox);
    yLabel = createLabel(this->parentWidget(), "yLabel", "y:     ");
    ySpinBox = createSpinBox(this->parentWidget(), "ySpinBox", 90, 0, 1000, 0);
    coordLayout->addRow(yLabel, ySpinBox);

    drawButton = createPushButton(this->parentWidget(), "drawButton", "Draw", 90);
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
    MainWidget::instance()->removeDrawnShape(drawnShapeIndex);
    
    QString newShapeToDraw = shapesComboBox->currentText();
    MainWidget::instance()->setCurrentShape(newShapeToDraw);
}

void SideBar::handleDrawButtonClick() {
    Shape* drawingShape = MainWidget::instance()->getCurrentShape();

    Point center(xSpinBox->value(), ySpinBox->value());
    drawingShape->setCenter(center);

    if (drawingShape->calculatePoints()) {
        if (drawingShape->isDrawn()) {      // Keep the drawn shape as current in case the user wants to move or edit that shape again
            MainWidget::instance()->redrawShapes();
            MainWidget::instance()->setCurrentShape(drawingShape);
        }
        else {
            MainWidget::instance()->addNewShape(drawingShape);
            drawingShape->setDrawn();
            MainWidget::instance()->setCurrentShape(drawingShape->getName(),    // Create a new current shape
                                                    drawingShape->getData());   // with data from the drawn shape
        }
    }
}

QSpinBox* SideBar::createSpinBox(QWidget* parent, const std::string qtObjName,
                                 int maxWidth, int minValue, int maxValue, int defaultValue) {
    QSpinBox* spinBox = new QSpinBox(parent);
    spinBox->setObjectName(qtObjName);
    spinBox->setMaximumSize(QSize(maxWidth, 16777215));
    spinBox->setRange(minValue, maxValue);
    spinBox->setValue(defaultValue);
    return spinBox;
}

QPushButton* SideBar::createPushButton(QWidget* parent, const char* qtObjName,
                                       const char* buttonText, int maxWidth) {
    QPushButton* pushButton = new QPushButton(buttonText, parent);
    pushButton->setObjectName(qtObjName);
    pushButton->setMaximumSize(QSize(maxWidth, 16777215));
    return pushButton;
}

void SideBar::createShapeDataArea(int spacing, int maxWidth) {
    shapeDataGroupBox = new QGroupBox("Shape Data", this->parentWidget());
    shapeDataGroupBox->setMaximumSize(QSize(maxWidth, 16777215));

    shapeDataLayout = new QFormLayout(this->parentWidget());
    shapeDataLayout->setSpacing(spacing);
    shapeDataLayout->setObjectName("shapeDataLayout");

    shapeDataGroupBox->setLayout(shapeDataLayout);
    this->addLayout(shapeDataLayout);
    this->addWidget(shapeDataGroupBox);
}
