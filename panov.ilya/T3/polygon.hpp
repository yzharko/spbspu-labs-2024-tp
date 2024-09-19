#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "point.hpp"

namespace panov
{
    struct Polygon
    {
        std::vector<Point> points;
        bool operator==(const Polygon& other) const;

        double area() const;
    };
}

#endif
