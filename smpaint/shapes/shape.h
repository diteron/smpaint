#pragma once

#include <vector>
#include <cmath>
#include <qpainter.h>
#include <point.h>

class DataField;

class Shape {
public:
    typedef int property;
    enum Properties{
        Const,
        Scalable
    };

    Shape(QString name) : _name(name) {};

    void setCenter(Point point) { _centerCoord = point; };
    void setCenterXCoord(int x) { _centerCoord.setX(x); }
    void setCenterYCoord(int y) { _centerCoord.setY(y); }
    void setData(const QVector<std::pair<int, property>>& data) { _data = data; };
    void setData(int dataInd, int newValue) { _data[dataInd].first = newValue; };
    void setPoints(QVector<Point> points) { _points = points; }
    void setBorderColor(const QColor& borderColor) { _borderColor = borderColor; }
    void setDrawn() { _drawn = true; }
    void setMoved() { _moved = true; }
    
    const Point& getCenter() { return _centerCoord; };
    QVector<std::pair<int, property>>& getData() { return _data; };
    const QVector<DataField>& getDataFields() { return _dataFields; };
    const QVector<Point>& getPoints() { return _points; };
    const QColor& getBorderColor() { return _borderColor; }
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
    QVector<std::pair<int, property>> _data;
    QVector<DataField> _dataFields;
    QVector<Point> _points;
    QColor _borderColor = Qt::black;
    bool _drawn = false;
    bool _moved = false;
};

class DataField {
public:
    DataField(QString fieldName, int defaultValue, Shape::property property)
        : _fieldName(fieldName), _defaultValue(defaultValue), _property(property) {};
    const QString& getFieldName() { return _fieldName; };
    int getDefaultValue() { return _defaultValue; };
    Shape::property getProperty() { return _property; }

private:
    QString _fieldName;
    int _defaultValue;
    Shape::property _property;
};
