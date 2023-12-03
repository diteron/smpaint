#pragma once

#include <QWidget>
#include <QtPlugin>
#include "../shapes/shape.h"

class ISmpPlugin {
public:
    virtual ~ISmpPlugin() = default;
    virtual void setupUi() = 0;
    virtual void setCurrentShape(Shape* shape) = 0;
    virtual QWidget* getPluginLabel() const = 0;
    virtual QWidget* getPluginField() const = 0;
};

#define ISmpPlugin_iid "SmpPlugin"
Q_DECLARE_INTERFACE(ISmpPlugin, ISmpPlugin_iid)
