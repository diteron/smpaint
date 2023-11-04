#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"

class MainWidget : public QWidget {
public:
    MainWidget(QWidget* parent = nullptr);
    void setupUi(QMainWindow* SmpaintClass);

private:
    QGridLayout* gridLayout = nullptr;
    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    void createGridLayout();
    void createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                          const QColor& backgroundColor);
};

