#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"

class MainWidget : public QWidget {
public:
    MainWidget(QWidget* parent = nullptr);
    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);

private:
    QMenuBar* menuBar = nullptr;
    QMenu* menuFile = nullptr;
    QAction* openAction = nullptr;
    QAction* saveAction = nullptr;

    QGridLayout* gridLayout = nullptr;

    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;

    SideBar* sideBar = nullptr;

    void createGridLayout();
    void createDrawCanvas(const QRect& startGeometry, const QSize& minSize,
                          const QColor& backgroundColor);
    void createMenuBar(QMainWindow* SmpaintClass);
    void addMenuBarSubmenu(QMenu** submenu, const char* submenuName,
                           const char* title, const char* parentName);
    void addSubmenuAction(QMenu* submenu, QAction** action, const char* actionName,
                          QWidget* parent, const char* parentName,
                          const char* title, const char* shortcut);
};

