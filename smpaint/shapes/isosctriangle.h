#pragma once

#include "shape.h"
#include "shapefactory.h"

class IsoscTriangle : public Shape {
public:
    IsoscTriangle();
    bool calculatePoints();

private:
    void createFields();

    static const bool registeredShape;
};

