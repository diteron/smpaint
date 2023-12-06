#pragma once

#include <QObject>
#include <QPushButton>
#include <QtPlugin>
#include <ismpplugin.h>
#include <smpdrawer.h>

class SmpColorizer : public QObject, public ISmpPlugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "SmpColorizer" FILE "smpcolorizer.json")
    Q_INTERFACES(ISmpPlugin)

public:
    void setupUi() override;
    void registerDrawer(void* drawer) override { drawerInstance = static_cast<SmpDrawer*>(drawer);  }
    void mousePress() override {};

    QWidget* getPluginLabel() const override { return colorButton; }
    QWidget* getPluginField() const override { return field; }

public slots:
    void handleColorButtonClick();

private:
    SmpDrawer* drawerInstance = nullptr;
    QPushButton* colorButton = nullptr;
    QWidget* field = nullptr;
};
