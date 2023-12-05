#pragma once

#include <QObject>
#include <QPushButton>
#include <QtPlugin>
#include <QDoubleSpinBox>
#include "../smpaint/plugins/ismpplugin.h"
#include "../smpaint/smpdrawer.h"

class ShapeScaler : public QObject, public ISmpPlugin {
    
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ShapeScaler" FILE "shapescaler.json")
    Q_INTERFACES(ISmpPlugin)

public:
    void setupUi() override;
    void registerDrawer(void * drawer) override { drawerInstance = static_cast<SmpDrawer*>(drawer); }
    void mousePress() override {};

    QWidget* getPluginLabel() const override { return scaleSpinBox; }
    QWidget* getPluginField() const override { return scaleButton; }

public slots:
    void handleScaleButtonClick();

private:
    QDoubleSpinBox* createDoubleSpinBox(int precision, double step, double defaultValue,
                                        double minValue, double maxValue, const QString& prefix);
    void scaleShape(Shape* shape);

    SmpDrawer* drawerInstance = nullptr;
    QDoubleSpinBox* scaleSpinBox = nullptr;
    QPushButton* scaleButton = nullptr;
};
