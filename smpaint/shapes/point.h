#pragma once

#include <qpoint.h>

class Point : public QPoint {
public:
    Point(int xPos, int yPos);
    Point(int xPos, int yPos, bool isEndPoint);
    Point(QPoint point) : endPoint(false) {
        this->setX(point.x());
        this->setY(point.y());
    };

    void setAsEndPoint();
    bool isEndPoint();

private:
    bool endPoint = false;
};
