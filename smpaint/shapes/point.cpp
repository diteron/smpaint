#include "stdafx.h"
#include "point.h"

Point::Point() {}

Point::Point(int xPos, int yPos) 
    : _x(xPos), _y(yPos), _endPoint(false) {}

Point::Point(int xPos, int yPos, bool isEndPoint) 
    : _x(xPos), _y(yPos), _endPoint(isEndPoint) {}

Point::Point(QPoint point) : _endPoint(false) {
    _x = point.x();
    _y = point.y();
}

Point::operator QPoint() const {
    QPoint qpoint(_x, _y);
    return qpoint;
}

QDataStream& operator<<(QDataStream& out, const Point& point) {
    out << point._x
        << point._y
        << point._endPoint;
    return out;
}

QDataStream& operator>>(QDataStream& in, Point& point) {
    in >> point._x
       >> point._y
       >> point._endPoint;
    return in;
}
