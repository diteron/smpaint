#include "stdafx.h"
#include "shape.h"

QDataStream& operator<<(QDataStream& out, const Shape& shape) {
    out << shape._name
        << shape._centerCoord
        << shape._data
        << shape._points
        << shape._borderColor;

    return out;
}

QDataStream& operator>>(QDataStream& in, Shape& shape) {
    in >> shape._centerCoord
        >> shape._data
        >> shape._points
        >> shape._borderColor;

    return in;
}
