#pragma once

#include "ui/mainwidget.h"

#define MAIN_WND_WIDTH 1100
#define MAIN_WND_HEIGHT 620

class Smpaint : public QMainWindow {
public:
    Smpaint(QWidget *parent = nullptr);
    ~Smpaint();

private:
    MainWidget* centralWidget = nullptr;
};
