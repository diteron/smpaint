#pragma once

//#include <qwidget.h>
#include "../shapes/shape.h"

class DrawCanvas : public QWidget {

    Q_OBJECT

public:
    DrawCanvas(QWidget* parent, const QRect& startGeometry,
               const QSizePolicy& sizePolicy, const QSize& minSize,
               const QPalette& backgroundColor);
    void setSize(const QSizePolicy& sizePolicy, const QSize& minSize, const QSize& baseSize);
    void setBackgroundColor(const QPalette &palette);
    void setResizable();

private:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void drawShapes(QPainter& painter, const QVector<Shape*>& shapes);
    QPen createPen(int width, Qt::PenStyle style, const QColor& color);
};
