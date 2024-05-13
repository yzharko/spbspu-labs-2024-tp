#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include "Point.hpp"

struct Polygon
{
    std::vector< Point > points;
};

bool operator==(const Polygon& lhs, const Polygon& rhs);

#endif
