#include "stdafx.h"
#include "smpaint.h"


Smpaint::Smpaint(QWidget* parent) : QMainWindow(parent) {
    setCentralWidget(MainWidget::getInstance());
    MainWidget::getInstance()->setObjectName("mainWidget");
    setCentralWidget(MainWidget::getInstance());
    MainWidget::getInstance()->setupUi(this, 1000, 550);
}

Smpaint::~Smpaint() {

}

