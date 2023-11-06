#include "stdafx.h"
#include "drawcanvas.h"

DrawCanvas::DrawCanvas(QWidget* parent, const QRect& startGeometry,
                       const QSizePolicy& sizePolicy, const QSize& minSize,
                       const QPalette& backgroundColor) : QWidget(parent) {
    this->setObjectName("drawCanvas");
    this->setGeometry(startGeometry);
    this->setSize(sizePolicy, minSize, QSize(0, 0));
    this->setBackgroundColor(backgroundColor);
}

void DrawCanvas::setSize(const QSizePolicy &sizePolicy, const QSize &minSize, const QSize &baseSize) {
    this->setSizePolicy(sizePolicy);
    this->setMinimumSize(minSize);
    this->setBaseSize(baseSize);
}

void DrawCanvas::setBackgroundColor(const QPalette &palette) {
    this->setPalette(palette);
}

void DrawCanvas::setResizable() {
    this->setWindowFlags(Qt::SubWindow);
    QSizeGrip* sizeGrip = new QSizeGrip(this);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(sizeGrip, 0, 0, 1, 1, Qt::AlignBottom | Qt::AlignRight);
}
