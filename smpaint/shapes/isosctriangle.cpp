#include "stdafx.h"
#include "isosctriangle.h"

const bool IsoscTriangle::registeredShape = ShapeFactory::registerShape("Isosceles triangle", shapeBuilder<IsoscTriangle>);
const char* IsoscTriangle::name = "Isosceles triangle";

void IsoscTriangle::calculatePoints() {
    int halfBase = static_cast<int>(sqrt((_data[1]) ^ 2 - _data[0] ^ 2));
    int thirdOfHeigh = static_cast<int>(_data[0] / 3);

    _points = { Point(_centerCoord.x(), _centerCoord.y() - (2 * thirdOfHeigh)),
                Point(_centerCoord.x() - halfBase, _centerCoord.y() + thirdOfHeigh),
                Point(_centerCoord.x() + halfBase, _centerCoord.y() + thirdOfHeigh),
                _points[0].setAsEndPoint() };
}

void IsoscTriangle::createFields() {
    _fields = { DataField("Heigh", 50),
                DataField("Side", 60) };

}

