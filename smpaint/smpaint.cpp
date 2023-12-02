#include "stdafx.h"
#include "smpaint.h"

Smpaint::Smpaint(QWidget* parent) : QMainWindow(parent) {
    setCentralWidget(MainWidget::instance());
    setCentralWidget(MainWidget::instance());
    MainWidget::instance()->setupUi(this, 1100, 620);
}

Smpaint::~Smpaint() {
    delete MainWidget::instance();
}

