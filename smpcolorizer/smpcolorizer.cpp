#include "stdafx.h"
#include "smpcolorizer.h"

void SmpColorizer::setupUi() {
    colorButton = new QPushButton("Color");
    colorButton->setMaximumSize(QSize(80, 16777215));
    colorButton->connect(colorButton, &QPushButton::clicked,
                         this, &SmpColorizer::handleColorButtonClick);
}

void SmpColorizer::handleColorButtonClick() {
    if (currentShape) {
        QColor color = QColorDialog::getColor(Qt::black, nullptr);
        if (color.isValid()) { currentShape->setBorderColor(color); }
    }
}
