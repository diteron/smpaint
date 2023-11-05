#pragma once

#include <QtWidgets/QMainWindow>
#include "mainwidget.h"
#include "ui_smpaint.h"

class Smpaint : public QMainWindow {
public:
    Smpaint(QWidget *parent = nullptr);
    ~Smpaint();
};
