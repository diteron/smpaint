#pragma once
#include "shape.h"
#include "shapefactory.h"

class Rectangle : public Shape {
public:
    Rectangle();
    bool calculatePoints() override;

private:
    void createFields() override;

    static const bool registeredShape;
};

