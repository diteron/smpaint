#pragma once

#include "shape.h"
#include "shapefactory.h"

class Parallelogram : public Shape {
public:
    Parallelogram();
    bool calculatePoints() override;

private:
    void createFields() override;
    float toRad(int degree);

    static const bool registeredShape;
};
