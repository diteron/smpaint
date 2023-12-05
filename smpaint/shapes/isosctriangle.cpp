#include "stdafx.h"
#include "isosctriangle.h"

const bool IsoscTriangle::registeredShape = ShapeFactory::instance()->registerShape("Isosceles triangle", shapeBuilder<IsoscTriangle>);

IsoscTriangle::IsoscTriangle() : Shape("Isosceles triangle") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(std::make_pair(_dataFields[i].getDefaultValue(), _dataFields[i].getProperty()));
    }
}

bool IsoscTriangle::calculatePoints() {
    int heightLength = _data[0].first;
    int sideLength = _data[1].first;
    if (heightLength >= sideLength)
        return false;
    int halfBase = static_cast<int>(sqrt((sideLength * sideLength) - (heightLength * heightLength)));
    int thirdOfHeight = static_cast<int>(heightLength / 3);

    _points = { Point(_centerCoord.x(), _centerCoord.y() - (2 * thirdOfHeight)),
                Point(_centerCoord.x() - halfBase, _centerCoord.y() + thirdOfHeight),
                Point(_centerCoord.x() + halfBase, _centerCoord.y() + thirdOfHeight) };
    // Close shape points
    Point endPoint = _points[0];
    _points.append(endPoint.setAsEndPoint());
    return true;
}

void IsoscTriangle::createFields() {
    _dataFields = { DataField("Height", 50, Shape::Scalable),
                    DataField("Side", 60, Shape::Scalable) };
}
