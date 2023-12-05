#include "stdafx.h"
#include "rectangle.h"

const bool Rectangle::registeredShape = ShapeFactory::instance()->registerShape("Rectangle", shapeBuilder<Rectangle>);

Rectangle::Rectangle() : Shape("Rectangle") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(std::make_pair(_dataFields[i].getDefaultValue(), _dataFields[i].getProperty()));
    }
}

bool Rectangle::calculatePoints() {
    int halfWidth = static_cast<int>(_data[0].first / 2);
    int halfHeight = static_cast<int>(_data[1].first / 2);

    _points = { Point(_centerCoord.x() - halfWidth, _centerCoord.y() + halfHeight),
                Point(_centerCoord.x() - halfWidth, _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + halfWidth, _centerCoord.y() - halfHeight),
                Point(_centerCoord.x() + halfWidth, _centerCoord.y() + halfHeight) };
    // Close shape points
    Point endPoint = _points[0];
    _points.append(endPoint.setAsEndPoint());

    return true;
}

void Rectangle::createFields() {
    _dataFields = { DataField("Width", 50, Shape::Scalable),
                    DataField("Height", 60, Shape::Scalable) };
}

