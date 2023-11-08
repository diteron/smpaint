#include "stdafx.h"
#include "shapefactory.h"

ShapeFactory* ShapeFactory::_instance = nullptr;

bool ShapeFactory::registerShape(std::string const& shapeName, ShapeBuilder const& builder) {
    return getShapeFactory()->_registry.insert(std::make_pair(shapeName, builder)).second;
}

Shape* ShapeFactory::buildShape(std::string const& shapeName) {
    auto it = getShapeFactory()->_registry.find(shapeName);
    if (it == getShapeFactory()->_registry.end()) { return nullptr; }
    return (it->second)();
}

std::vector<std::string> ShapeFactory::getShapesNames() {
    std::vector<std::string> names;
    for (const std::pair shape : getShapeFactory()->_registry) {
        names.push_back(shape.first);
    }
    return names;
}

ShapeFactory* ShapeFactory::getShapeFactory() {
    if (_instance == nullptr) {
        _instance = new ShapeFactory();
    }
    return _instance;
}
