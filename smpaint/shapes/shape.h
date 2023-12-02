#pragma once

#include <vector>
#include <cmath>
#include <qpainter.h>
#include "point.h"

class DataField;

class Shape {
public:
    Shape(QString name) : _name(name) {};

    void setCenter(Point point) { _centerCoord = point; };
    void setCenterXCoord(int x) { _centerCoord.setX(x); }
    void setCenterYCoord(int y) { _centerCoord.setY(y); }
    void setData(const QVector<int>& data) { _data = data; };
    void setData(int dataInd, int newValue) { _data[dataInd] = newValue; };
    void setDrawn() { _drawn = true; }
    void setMoved() { _moved = true; }
    
    const Point& getCenter() { return _centerCoord; };
    QVector<int>& getData() { return _data; };
    const QVector<DataField>& getDataFields() { return _dataFields; };
    const QVector<Point>& getPoints() { return _points; };
    const QString getName() { return _name; }
    const bool isDrawn() { return _drawn; }
    const bool isMoved() { return _moved; }

    friend QDataStream& operator<<(QDataStream& out, const Shape& shape);
    friend QDataStream& operator>>(QDataStream& in, Shape& shape);

    virtual bool calculatePoints() = 0;

protected:
    virtual void createFields() = 0;

    template <typename derivedShape>
    static Shape* shapeBuilder() { return new derivedShape(); }

    const QString _name;
    Point _centerCoord;
    QVector<int> _data;
    QVector<DataField> _dataFields;
    QVector<Point> _points;
    bool _drawn = false;
    bool _moved = false;
};

class DataField {
public:
    DataField(const char* fieldName, int defaultValue)
        : _fieldName(fieldName), _defaultValue(defaultValue) {};
    const QString& getFieldName() { return _fieldName; };
    int getDefaultValue() { return _defaultValue; };

private:
    const QString _fieldName;
    int _defaultValue;
};
