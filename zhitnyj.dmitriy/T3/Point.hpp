#ifndef POINT_HPP
#define POINT_HPP

struct Point
{
    int x;
    int y;
};

bool operator==(const Point& lhs, const Point& rhs);

#endif
