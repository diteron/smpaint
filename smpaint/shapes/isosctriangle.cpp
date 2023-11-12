#include "stdafx.h"
#include "isosctriangle.h"

const bool IsoscTriangle::registeredShape = ShapeFactory::instance()->registerShape("Isosceles triangle", shapeBuilder<IsoscTriangle>);

IsoscTriangle::IsoscTriangle() : Shape("Isosceles triangle") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(_dataFields[i].getDefaultValue());
    }
}

bool IsoscTriangle::calculatePoints() {
    if (_data[0] >= _data[1])
        return false;
    int halfBase = static_cast<int>(sqrt((_data[1] * _data[1]) - (_data[0] * _data[0])));
    int thirdOfHeight = static_cast<int>(_data[0] / 3);

    _points = { Point(_centerCoord.x(), _centerCoord.y() - (2 * thirdOfHeight)),
                Point(_centerCoord.x() - halfBase, _centerCoord.y() + thirdOfHeight),
                Point(_centerCoord.x() + halfBase, _centerCoord.y() + thirdOfHeight) };
    _points.append(_points[0].setAsEndPoint());     // Close shape points
    return true;
}

void IsoscTriangle::createFields() {
    _dataFields = { DataField("Height", 50),
                    DataField("Side", 60) };

}
