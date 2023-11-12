#include "stdafx.h"
#include "point.h"

Point::Point() {}

Point::Point(int xPos, int yPos) : QPoint(xPos, yPos) {}

Point::Point(int xPos, int yPos, bool isEndPoint) 
    : QPoint(xPos, yPos), _endPoint(isEndPoint) {}

Point& Point::setAsEndPoint() { _endPoint = true; return *this; }

bool Point::isEndPoint() { return _endPoint; }
