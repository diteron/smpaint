#include "stdafx.h"
#include "shapefactory.h"

ShapeFactory* ShapeFactory::_instance = nullptr;

bool ShapeFactory::registerShape(const QString& shapeName, ShapeBuilder const& builder) {
    return _registry.insert(std::make_pair(shapeName, builder)).second;
}

Shape* ShapeFactory::buildShape(const QString& shapeName) {
    auto it = _registry.find(shapeName);
    if (it == _registry.end()) { return nullptr; }
    return (it->second)();
}

QStringList ShapeFactory::getShapesNames() {
    QStringList names;
    for (const std::pair shape : _registry) {
        names.push_back(shape.first);
    }
    return names;
}

ShapeFactory* ShapeFactory::instance() {
    if (_instance == nullptr) {
        _instance = new ShapeFactory();
    }
    return _instance;
}
