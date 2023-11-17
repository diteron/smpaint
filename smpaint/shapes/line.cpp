#include "stdafx.h"
#include "line.h"

const bool Line::registeredShape = ShapeFactory::instance()->registerShape("Line", shapeBuilder<Line>);

Line::Line() : Shape("Line") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(_dataFields[i].getDefaultValue());
    }
}

bool Line::calculatePoints() {
    float angleInRad = toRad(_data[1]);
    int halfLength = static_cast<int>(_data[0] / 2);
    int xOffset = static_cast<int>(halfLength * cos(angleInRad));
    int yOffset = static_cast<int>(halfLength * sin(angleInRad));

    _points = { Point(_centerCoord.x() - xOffset, _centerCoord.y() + yOffset),
                Point(_centerCoord.x() + xOffset, _centerCoord.y() - yOffset) };
    _points[1].setAsEndPoint();

    return true;
}

void Line::createFields() {
    _dataFields = { DataField("Length", 150),
                    DataField("Angle", 0) };
}

float Line::toRad(int degree) {
    return (degree * (M_PI / 180));
}
