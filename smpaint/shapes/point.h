#pragma once

#include <qpoint.h>

class Point {
public:
    Point();
    Point(int xPos, int yPos);
    Point(int xPos, int yPos, bool isEndPoint);
    Point(QPoint point);

    int x() const { return _x; }
    int y() const { return _y; }
    bool isEndPoint() const { return _endPoint; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    Point& setAsEndPoint() { _endPoint = true; return *this; }

    operator QPoint() const;
    friend QDataStream& operator<<(QDataStream& out, const Point& shape);
    friend QDataStream& operator>>(QDataStream& in, Point& shape);

private:
    int _x = 0;
    int _y = 0;
    bool _endPoint = false;
};
