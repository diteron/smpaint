#include "stdafx.h"
#include "parallelogram.h"

const bool Parallelogram::registeredShape = ShapeFactory::instance()->registerShape("Parallelogram",
                                                                                    shapeBuilder<Parallelogram>);

Parallelogram::Parallelogram() : Shape("Parallelogram") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(_dataFields[i].getDefaultValue());
    }
}

bool Parallelogram::calculatePoints() {
    float angleInRad = toRad(_data[2]);
    int halfSideX = static_cast<int>(_data[0] / 2);
    int halfSideY = static_cast<int>(_data[1] / 2);
    int halfHeight = static_cast<int>((_data[1] * sin(angleInRad)) / 2);

    /*     _________________
          /       /        /
         /-------/--------/
        /_______/_|______/ 
                 ^
           halfSideXPart
    */
    int halfSideXPart = static_cast<int>(halfSideY * cos(angleInRad));

    _points = { Point(_centerCoord.x() - (halfSideX + halfSideXPart), _centerCoord.y() + halfHeight),
                Point(_centerCoord.x() - (halfSideX - halfSideXPart), _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + (halfSideX + halfSideXPart), _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + (halfSideX - halfSideXPart), _centerCoord.y() + halfHeight) };
    // Close shape points
    Point endPoint = _points[0];
    _points.append(endPoint.setAsEndPoint());

    return true;
}

void Parallelogram::createFields() {
    _dataFields = { DataField("Side x", 90),
                    DataField("Side y", 70),
                    DataField("Angle", 45) };
}

float Parallelogram::toRad(int degree) {
    return (degree * (M_PI / 180));
}
