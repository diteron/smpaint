#pragma once

#include <qwidget.h>
#include "ui/drawcanvas.h"
#include "ui/sidebar.h"

class MainWidget : public QWidget {

    Q_OBJECT

public:
    MainWidget(QWidget* parent = nullptr);
    void setupUi(QMainWindow* SmpaintClass, int windowWidth, int windowHeight);
    static MainWidget* getInstance();

private:
    static MainWidget* instance;

    QMenuBar* menuBar = nullptr;
    QMenu* menuFile = nullptr;
    QAction* openAction = nullptr;
    QAction* saveAction = nullptr;

    QGridLayout* gridLayout = nullptr;

    QScrollArea* scrollArea = nullptr;
    DrawCanvas* drawCanvas = nullptr;

    SideBar* sideBar = nullptr;

    QGridLayout* createGridLayout();
    DrawCanvas* createDrawCanvas(const QRect& startGeometry, const QSize& minSize, // TODO: Change function return value to DrawCanvas*
                          const QColor& backgroundColor);
    QSizePolicy createExpandSizePolicy(int horizontalStretch, int verticalStretch);
    QPalette createPalette(const QColor& backgroundColor);
    QMenuBar* createMenuBar(QMainWindow* SmpaintClass);
    void addMenuBarSubmenu(QMenuBar* menuBar, QMenu** submenu, const char* submenuName,
                           const char* title, const char* parentName);
    void addSubmenuAction(QMenu* submenu, QAction** action, const char* actionName,
                          QWidget* parent, const char* parentName,
                          const char* title, const char* shortcut);
};

