#pragma once

#include <qwidget.h>

class DrawCanvas : public QWidget {

    Q_OBJECT

public:
    DrawCanvas(QWidget* parent = nullptr);
    void setSize(QSizePolicy& sizePolicy, const QSize& minSize, const QSize& baseSize);
    void setBackgroundColor(QPalette &palette);
    void setResizable();
};

