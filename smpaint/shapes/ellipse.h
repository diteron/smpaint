#pragma once
#include "shape.h"
#include "shapefactory.h"

class Ellipse : public Shape {
public:
    Ellipse();
    bool calculatePoints() override;

private:
    void createFields() override;

    static const bool registeredShape;
};

