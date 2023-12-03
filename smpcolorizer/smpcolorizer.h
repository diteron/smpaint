#pragma once

#include <QObject>
#include <QPushButton>
#include <QtPlugin>
#include "../smpaint/plugins/ismpplugin.h"
#include "../smpaint/mainwidget.h"

class SmpColorizer : public QObject, public ISmpPlugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SmpColorizer" FILE "smpcolorizer.json")
    Q_INTERFACES(ISmpPlugin)

public:
    void setupUi() override;
    void setCurrentShape(Shape* shape) override { currentShape = shape; }
    QWidget* getPluginLabel() const override { return colorButton; }
    QWidget* getPluginField() const override { return field; }

public slots:
    void handleColorButtonClick();

private:


    Shape* currentShape = nullptr;
    QPushButton* colorButton = nullptr;
    QWidget* field = nullptr;
};
