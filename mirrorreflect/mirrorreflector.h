#pragma once

#include <QObject>
#include <QPushButton>
#include <QtPlugin>
#include "../smpaint/plugins/ismpplugin.h"
#include "../smpaint/mainwidget.h"

class MirrorReflector : public QObject, public ISmpPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "MirrorReflector" FILE "mirrorreflector.json")
    Q_INTERFACES(ISmpPlugin)

public:
    void setupUi() override;
    void registerMainWidget(void* mainWidgetInst) override { mainWidgetInstance = static_cast<MainWidget*>(mainWidgetInst); }
    void mousePress() override;

    QWidget* getPluginLabel() const override { return mirrorButton; }
    QWidget* getPluginField() const override { return field; }

public slots:
    void handleMirrorButtonClick();

private:
    void calculateMirrorImage(Shape* mirror);
    float findCoefficientA(const Point& point1, const Point& point2);
    float findCoefficientC(const Point& point1, const Point& point2);
    Point reflectPoint(const Point& point, float mirrorCoeffA, float mirrorCoeffB, float mirrorCoeffC);

    Shape* reflectedShape = nullptr;
    MainWidget* mainWidgetInstance = nullptr;
    QPushButton* mirrorButton = nullptr;
    QWidget* field = nullptr;
};
