#include "stdafx.h"
#include "smpcolorizer.h"

void SmpColorizer::setupUi() {
    colorButton = new QPushButton("Color");
    colorButton->setMaximumSize(QSize(100, 16777215));
    colorButton->setMinimumWidth(80);
    colorButton->connect(colorButton, &QPushButton::clicked,
                         this, &SmpColorizer::handleColorButtonClick);
}

void SmpColorizer::handleColorButtonClick() {
    Shape* currentShape = drawerInstance->getCurrentShape();
    if (currentShape) {
        QColor color = QColorDialog::getColor(Qt::black, nullptr);
        if (color.isValid()) { currentShape->setBorderColor(color); }
    }
}
