#pragma once

#include <qpoint.h>

class Point : public QPoint {
public:
    Point();
    Point(int xPos, int yPos);
    Point(int xPos, int yPos, bool isEndPoint);
    Point(QPoint point) : _endPoint(false) {
        this->setX(point.x());
        this->setY(point.y());
    };

    Point& setAsEndPoint();
    bool isEndPoint();

private:
    bool _endPoint = false;
};
