#pragma once

#include "shape.h"
#include "shapefactory.h"

class Line : public Shape {
public:
    Line();
    bool calculatePoints() override;

private:
    void createFields() override;
    float toRad(int degree);

    static const bool registeredShape;
};
