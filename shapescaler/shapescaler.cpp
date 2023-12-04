#include "stdafx.h"
#include "shapescaler.h"

void ShapeScaler::setupUi() {
    scaleButton = new QPushButton("Set scale");
    scaleButton->setMaximumSize(QSize(100, 16777215));
    scaleButton->setMinimumWidth(80);
    scaleButton->connect(scaleButton, &QPushButton::clicked,
                          this, &ShapeScaler::handleScaleButtonClick);
    scaleSpinBox = createDoubleSpinBox(1, 0.1, 1.0,
                                       0.1, 5.0, "x");
}

QDoubleSpinBox* ShapeScaler::createDoubleSpinBox(int precision, double step, double defaultValue,
                                                 double minValue, double maxValue, const QString& prefix) {
    QDoubleSpinBox* dSpinBox = new QDoubleSpinBox();
    dSpinBox->setMinimumWidth(80);
    dSpinBox->setDecimals(precision);
    dSpinBox->setSingleStep(step);
    dSpinBox->setValue(defaultValue);
    dSpinBox->setRange(minValue, maxValue);
    dSpinBox->setPrefix(prefix);
    return dSpinBox;
}

void ShapeScaler::scaleShape(Shape* shape) {
    QVector<int> shapeData = shape->getData();
    double scale = scaleSpinBox->value();
    for (int& dataValue : shapeData) {
        dataValue = static_cast<int>(round(dataValue * scale));
    }
    shape->setData(shapeData);
}

void ShapeScaler::handleScaleButtonClick() {
    Shape* currentShape = mainWidgetInstance->getCurrentShape();
    if (!currentShape->isDrawn()) {
        QApplication::beep();
        QMessageBox::information(0, "Hint", "Select drawn shape");
        return;
    }
    scaleShape(currentShape);
    QApplication::beep();
    QMessageBox::information(0, "Hint", "To redraw the shape click on the Draw Button");
}