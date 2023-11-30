#include "stdafx.h"
#include "../mainwidget.h"
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

void DrawCanvas::mousePressEvent(QMouseEvent* event) {
    Shape* drawingShape = MainWidget::instance()->getCurrentShape();
    drawingShape->setCenter(event->pos());

    if (drawingShape->calculatePoints()) {
        MainWidget::instance()->addNewShape(drawingShape);
        if (drawingShape->isDrawn()) {
            MainWidget::instance()->setCurrentShape(drawingShape);
        }
        else {
            drawingShape->setDrawn();
            MainWidget::instance()->setCurrentShape(drawingShape->getName(), drawingShape->getData());
        }
    }
}

void DrawCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.begin(this);
    drawShapes(painter, MainWidget::instance()->getShapesList());
    painter.end();
}

void DrawCanvas::drawShapes(QPainter& painter, const QVector<Shape*>& shapes) {
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    for (Shape* shape : shapes) {
        QVector<Point> points = shape->getPoints();
        for (unsigned i = 0; i < points.size() - 1; ++i) {
            painter.drawLine(points[i], points[i + 1]);
        }
    }
}
