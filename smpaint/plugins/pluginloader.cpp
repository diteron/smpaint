#include "stdafx.h"
#include "pluginloader.h"

PluginsLoader::PluginsLoader(QObject* drawer, QFormLayout* pluginsLayout)
    : _drawer(drawer), _pluginsLayout(pluginsLayout) {}

QVector<ISmpPlugin*> PluginsLoader::loadPlugins() {
    QDir pluginsDir = QDir(QCoreApplication::applicationDirPath());
    pluginsDir.cd("plugins");

    QString dirname = pluginsDir.dirName();
    const auto dirFiles = pluginsDir.entryList(QDir::Files);
    for (const QString& fileName : dirFiles) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject* plugin = loader.instance();
        if (plugin) {
            addPluginUi(plugin);
        }
    }
    return _pluginsList;
}

void PluginsLoader::addPluginUi(QObject* plugin) {
    auto iPlugin = qobject_cast<ISmpPlugin*>(plugin);
    iPlugin->setupUi();
    iPlugin->registerDrawer(_drawer);
    _pluginsLayout->addRow(iPlugin->getPluginLabel(), iPlugin->getPluginField());
    _pluginsList.append(iPlugin);
}
