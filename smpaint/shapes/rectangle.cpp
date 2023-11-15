#include "stdafx.h"
#include "rectangle.h"

const bool Rectangle::registeredShape = ShapeFactory::instance()->registerShape("Rectangle", shapeBuilder<Rectangle>);

Rectangle::Rectangle() : Shape("Rectangle") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(_dataFields[i].getDefaultValue());
    }
}

bool Rectangle::calculatePoints() {
    int halfWidth = static_cast<int>(_data[0] / 2);
    int halfHeight = static_cast<int>(_data[1] / 2);

    _points = { Point(_centerCoord.x() - halfWidth, _centerCoord.y() + halfHeight),
                Point(_centerCoord.x() - halfWidth, _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + halfWidth, _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + halfWidth, _centerCoord.y() + halfHeight) };
    _points.append(_points[0].setAsEndPoint());      // Close shape points

    return true;
}

void Rectangle::createFields() {
    _dataFields = { DataField("Width", 50),
                    DataField("Height", 60) };
}

