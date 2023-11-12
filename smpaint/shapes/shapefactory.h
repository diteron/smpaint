#pragma once

#include <map>
#include "shape.h"

class ShapeFactory {
public:
    static ShapeFactory* instance();

    typedef std::function<Shape* ()> ShapeBuilder;
    bool registerShape(const QString& shapeName, ShapeBuilder const& builder);
    Shape* buildShape(QString const& shapeName);
    QStringList getShapesNames();

private:
    static ShapeFactory* _instance;
    std::map<QString, ShapeBuilder> _registry;
};

