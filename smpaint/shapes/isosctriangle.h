#pragma once

#include "shape.h"
#include "shapefactory.h"

class IsoscTriangle : public Shape {
public:
    IsoscTriangle() {};
    void calculatePoints();

private:
    void createFields();
};

