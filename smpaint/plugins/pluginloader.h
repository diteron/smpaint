#pragma once

#include "ismpplugin.h"

class PluginsLoader {
public:
    PluginsLoader(QWidget* mainWidget, QFormLayout* pluginsLayout);
    QVector<ISmpPlugin*> loadPlugins();

private:
    void addPluginUi(QObject* plugin);

    QWidget* _mainWidget = nullptr;
    QFormLayout* _pluginsLayout = nullptr;
    QVector<ISmpPlugin*> _pluginsList;
};
