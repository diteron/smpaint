#pragma once

#include "ismpplugin.h"

class PluginsLoader {
public:
    PluginsLoader(QObject* drawer, QFormLayout* pluginsLayout);
    QVector<ISmpPlugin*> loadPlugins();

private:
    void addPluginUi(QObject* plugin);

    QObject* _drawer = nullptr;
    QFormLayout* _pluginsLayout = nullptr;
    QVector<ISmpPlugin*> _pluginsList;
};
