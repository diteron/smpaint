#pragma once

#include <qwidget.h>

class DrawCanvas : public QWidget {

    Q_OBJECT

public:
    DrawCanvas(QWidget* parent, const QRect& startGeometry,
               const QSizePolicy& sizePolicy, const QSize& minSize,
               const QPalette& backgroundColor);
    void setSize(const QSizePolicy& sizePolicy, const QSize& minSize, const QSize& baseSize);
    void setBackgroundColor(const QPalette &palette);
    void setResizable();
};

