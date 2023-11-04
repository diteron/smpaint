#include "stdafx.h"
#include "smpaint.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Smpaint mainWindow;
    mainWindow.show();
    return a.exec();
}
