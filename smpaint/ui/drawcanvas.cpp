#include "stdafx.h"
#include "drawcanvas.h"

// TODO: Change the constructor so that in the mainwidget, functionality of the createDrawCanvas function
// should be implemented in a new constructor 
DrawCanvas::DrawCanvas(QWidget* parent) : QWidget(parent) {}

void DrawCanvas::setSize(QSizePolicy &sizePolicy, const QSize &minSize, const QSize &baseSize) {
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(minSize);
    this->setBaseSize(baseSize);
}

void DrawCanvas::setBackgroundColor(QPalette &palette) {
    this->setPalette(palette);
}

void DrawCanvas::setResizable() {
    this->setWindowFlags(Qt::SubWindow);
    QSizeGrip* sizeGrip = new QSizeGrip(this);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(sizeGrip, 0, 0, 1, 1, Qt::AlignBottom | Qt::AlignRight);
}
