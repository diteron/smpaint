#pragma once

#include <vector>
#include <qpainter.h>
#include "point.h"
#include "field.h"

class Shape {
public:
    void setCenter(Point point) { _centerCoord = point; };
    void setData(std::vector<int>& data) { _data = data; };
    const std::vector<Field>& getFields() { return _fields; };
    const std::vector<Point>& getPoints() { return _points; };
    virtual void calculatePoints() const = 0;

protected:
    const char* name;
    Point _centerCoord;
    std::vector<int> _data;
    std::vector<int> _defaultData;
    std::vector<Field> _fields;
    std::vector<Point> _points;

    virtual void createFields() const = 0;
};

