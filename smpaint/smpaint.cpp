#include "stdafx.h"
#include "smpaint.h"
#include "smpdrawer.h"

Smpaint::Smpaint(QWidget* parent) : QMainWindow(parent) {
    centralWidget = new MainWidget(parent);
    setCentralWidget(centralWidget);
    centralWidget->setupUi(this, MAIN_WND_WIDTH, MAIN_WND_HEIGHT);
}

Smpaint::~Smpaint() {
    delete SmpDrawer::getInstance();
}

