#include "polygon.hpp"

anikanov::Polygon anikanov::Polygon::operator=(const anikanov::Polygon &polygon) {
    points = polygon.points;
    return *this;
}

size_t anikanov::Polygon::operator%(const size_t number) const {
    return points.size() % number;
}

anikanov::Point &anikanov::Polygon::operator[](size_t index) {
    return points[index];
}

size_t anikanov::Polygon::getSize() const {
    return points.size();
}

