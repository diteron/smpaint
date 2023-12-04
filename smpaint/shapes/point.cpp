#include "stdafx.h"
#include "point.h"

Point::Point() {}

Point::Point(int xPos, int yPos) : QPoint(xPos, yPos) {}

Point::Point(int xPos, int yPos, bool isEndPoint) 
    : QPoint(xPos, yPos), _endPoint(isEndPoint) {}

Point& Point::setAsEndPoint() { _endPoint = true; return *this; }

bool Point::isEndPoint() { return _endPoint; }

QDataStream& operator<<(QDataStream& out, const Point& point) {
    out << point.x()
        << point.y()
        << point._endPoint;
    return out;
}

QDataStream& operator>>(QDataStream& in, Point& point) {
    int x, y;
    in >> x
       >> y
       >> point._endPoint;
    point.setX(x);
    point.setY(y);
    return in;
}
