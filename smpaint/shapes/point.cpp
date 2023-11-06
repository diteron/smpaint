#include "stdafx.h"
#include "point.h"

Point::Point(int xPos, int yPos) : QPoint(xPos, yPos) {}

Point::Point(int xPos, int yPos, bool isEndPoint) 
    : QPoint(xPos, yPos), endPoint(isEndPoint) {}

void Point::setAsEndPoint() { endPoint = true; }

bool Point::isEndPoint() { return endPoint; }
