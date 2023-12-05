#include "stdafx.h"
#include "parallelogram.h"

const bool Parallelogram::registeredShape = ShapeFactory::instance()->registerShape("Parallelogram",
                                                                                    shapeBuilder<Parallelogram>);

Parallelogram::Parallelogram() : Shape("Parallelogram") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(std::make_pair(_dataFields[i].getDefaultValue(), _dataFields[i].getProperty()));
    }
}

bool Parallelogram::calculatePoints() {
    float angleInRad = toRad(_data[2].first);
    int halfSideX = static_cast<int>(_data[0].first / 2);
    int halfSideY = static_cast<int>(_data[1].first / 2);
    int halfHeight = static_cast<int>((_data[1].first * sin(angleInRad)) / 2);

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
    _dataFields = { DataField("Side x", 90, Shape::Scalable),
                    DataField("Side y", 70, Shape::Scalable),
                    DataField("Angle", 45, Shape::Const) };
}

float Parallelogram::toRad(int degree) {
    return (degree * (M_PI / 180));
}
