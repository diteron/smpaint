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
    void registerMainWidget(void* mainWidgetInst) override { mainWidgetInstance = static_cast<MainWidget*>(mainWidgetInst);  }
    void mousePress() override {};

    QWidget* getPluginLabel() const override { return colorButton; }
    QWidget* getPluginField() const override { return field; }

public slots:
    void handleColorButtonClick();

private:
    MainWidget* mainWidgetInstance = nullptr;
    QPushButton* colorButton = nullptr;
    QWidget* field = nullptr;
};
