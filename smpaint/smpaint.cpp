#include "stdafx.h"
#include "smpaint.h"


Smpaint::Smpaint(QWidget* parent) : QMainWindow(parent) {
    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
    mainWidget->setObjectName("mainWidget");
    setCentralWidget(mainWidget);
    mainWidget->setupUi(this);
}

Smpaint::~Smpaint() {

}

