#include "polygon.hpp"
#include <cmath>

namespace panov
{
    bool Polygon::operator==(const Polygon& other) const
    {
        return points == other.points;
    }

    double Polygon::area() const
    {
        double area = 0;
        int n = points.size();
        for (int i = 0; i < n; ++i)
        {
            int j = (i + 1) % n;
            area += points[i].x * points[j].y - points[j].x * points[i].y;
        }
        return std::abs(area) / 2.0;
    }
}
