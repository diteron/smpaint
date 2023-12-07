#pragma once

#include "drawcanvas.h"
#include "sidebar.h"
#include "menu.h"

class MainWidget : public QWidget {

    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);
    DrawCanvas* getDrawCanvas() { return drawCanvas; }
    SideBar* getSideBar() { return sideBar; }

private:
    void createGridLayout();
    void createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                          const QColor& backgroundColor);
    void createSideBar();
    QSizePolicy createExpandSizePolicy(int horizontalStretch, int verticalStretch);
    QPalette createPalette(const QColor& backgroundColor);

    SMenuBar* menuBar = nullptr;
    QGridLayout* gridLayout = nullptr;
    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;
    SideBar* sideBar = nullptr;

    const int DRAWCANV_WIDTH = 850;
    const int DRAWCANV_HEIGHT = 550;
    const int DRAWCANV_MIN_WIDTH = 100;
    const int DRAWCANV_MIN_HEIGHT = 50;
    const int SIDE_BAR_MAX_WIDTH = 200;
    const int SIDE_BAR_SPACING = 20;
    const int LAYOUTS_ITEMS_SPACING = 8;
    const int CONT_MARGINS = 11;
};
