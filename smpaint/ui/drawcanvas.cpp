#include "stdafx.h"
#include "../mainwidget.h"
#include "drawcanvas.h"

DrawCanvas::DrawCanvas(QWidget* parent, const QRect& startGeometry,
                       const QSizePolicy& sizePolicy, const QSize& minSize,
                       const QPalette& backgroundColor) : QWidget(parent) {
    this->setGeometry(startGeometry);
    this->setSize(sizePolicy, minSize, QSize(0, 0));
    this->setBackgroundColor(backgroundColor);
    this->setMouseTracking(true);
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
    if (!drawingShape->isDrawn()) {
        MainWidget::instance()->addNewShape(drawingShape);
        drawingShape->setDrawn();
    }

    Shape* lastShape = MainWidget::instance()->getLastShape();
    MainWidget::instance()->setCurrentShape(lastShape->getName(),    // Create a new current shape
                                            lastShape->getData());   // with data from the last drawn shape
}

void DrawCanvas::mouseMoveEvent(QMouseEvent* event) {
    Shape* movingShape = MainWidget::instance()->getCurrentShape();
    movingShape->setCenter(event->pos());

    if (movingShape->calculatePoints()) {
        if (!movingShape->isMoved()) { movingShape->setMoved(); }
        this->update();
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

    // Draw the current shape
    Shape* currentShape = MainWidget::instance()->getCurrentShape();
    if (!currentShape->isDrawn()) {
        QVector<Point> points = currentShape->getPoints();
        for (unsigned i = 0; i < points.size() - 1; ++i) {
            painter.drawLine(points[i], points[i + 1]);
        }
    }
    // Draw the shapes in the shapes list
    for (Shape* shape : shapes) {
        QVector<Point> points = shape->getPoints();
        for (unsigned i = 0; i < points.size() - 1; ++i) {
            painter.drawLine(points[i], points[i + 1]);
        }
    }
}
