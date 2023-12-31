#pragma once

#include "shape.h"
#include "shapefactory.h"

class IsoscTriangle : public Shape {
public:
    IsoscTriangle();
    bool calculatePoints() override;

private:
    void createFields() override;

    static const bool registeredShape;
};
