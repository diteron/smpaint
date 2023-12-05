#include "stdafx.h"
#include "ellipse.h"

const bool Ellipse::registeredShape = ShapeFactory::instance()->registerShape("Ellipse", shapeBuilder<Ellipse>);

Ellipse::Ellipse() : Shape("Ellipse") {
    createFields();
    for (unsigned i = 0; i < _dataFields.size(); ++i) {
        _data.append(std::make_pair(_dataFields[i].getDefaultValue(), _dataFields[i].getProperty()));
    }
}

bool Ellipse::calculatePoints() {
    const int pointsNum = 32;

    if (!_points.isEmpty()) {
        _points.clear();
    }

    int x, y;
    int xRadius = _data[0].first;
    int yRadius = _data[1].first;
    Point point;

    for (unsigned i = 0; i < pointsNum; ++i) {
        x = static_cast<int>(round(_centerCoord.x() + (xRadius * sin(2 * M_PI * i / pointsNum))));
        y = static_cast<int>(round(_centerCoord.y() + (yRadius * cos(2 * M_PI * i / pointsNum))));
        point.setX(x);
        point.setY(y);
        _points.append(point);
    }
    // Close shape points
    Point endPoint = _points[0];
    _points.append(endPoint.setAsEndPoint());

    return true;
}

void Ellipse::createFields() {
    _dataFields = { DataField("x radius", 50, Shape::Scalable),
                    DataField("y radius", 30, Shape::Scalable) };
}

