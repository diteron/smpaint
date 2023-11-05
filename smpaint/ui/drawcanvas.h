#pragma once

#include <qwidget.h>

class DrawCanvas : public QWidget {

    Q_OBJECT

public:
    void setSize(QSizePolicy& sizePolicy, const QSize& minSize, const QSize& baseSize);
    void setBackgroundColor(QPalette &palette);
    void setResizable();
};

