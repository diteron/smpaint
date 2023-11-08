#pragma once

#include <vector>
#include <math.h>
#include <qpainter.h>
#include "point.h"

class DataField;

class Shape {
public:
    void setCenter(Point point) { _centerCoord = point; };
    void setData(std::vector<int>& data) { _data = data; };
    const Point& getCenter() { return _centerCoord; };
    const std::vector<int>& getData() { return _data; };
    const std::vector<DataField>& getFields() { return _fields; };
    const std::vector<Point>& getPoints() { return _points; };

    virtual void calculatePoints() = 0;

protected:
    static const char* name;
    Point _centerCoord;
    std::vector<int> _data;
    std::vector<int> _defaultData;
    std::vector<DataField> _fields;
    std::vector<Point> _points;

    virtual void createFields() = 0;

    template <typename derivedShape>
    static Shape* shapeBuilder() { return new derivedShape(); }
    static const bool registeredShape;
};

class DataField {
public:
    DataField(const char* fieldName, int defaultValue)
        : _fieldName(fieldName), _defaultValue(defaultValue) {};
    const char* getFieldName() { return _fieldName; };
    int getDefaultValue() { return _defaultValue; };

private:
    const char* _fieldName;
    int _defaultValue;
};
