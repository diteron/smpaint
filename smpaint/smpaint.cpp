#include "stdafx.h"
#include "smpaint.h"


Smpaint::Smpaint(QWidget* parent) : QMainWindow(parent) {
    setCentralWidget(MainWidget::getMainWidget());
    MainWidget::getMainWidget()->setObjectName("mainWidget");
    setCentralWidget(MainWidget::getMainWidget());
    MainWidget::getMainWidget()->setupUi(this, 1000, 550);
}

Smpaint::~Smpaint() {

}

