#pragma once

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual void setupUi() const = 0;
    virtual void resetPluginState() const = 0;
};
