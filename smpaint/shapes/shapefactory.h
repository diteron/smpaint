#pragma once

#include <map>
#include "shape.h"

class ShapeFactory {
public:
    typedef std::function<Shape* ()> ShapeBuilder;
    static bool registerShape(std::string const& shapeName, ShapeBuilder const& builder);
    static Shape* buildShape(std::string const& shapeName);
    static std::vector<std::string> getShapesNames();

private:
    static ShapeFactory* getShapeFactory();
    static ShapeFactory* _instance;
    std::map<std::string, ShapeBuilder> _registry;
};

