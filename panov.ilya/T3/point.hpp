#ifndef POINT_HPP
#define POINT_HPP

namespace panov 
{
    struct Point 
    {
        int x, y;

        bool operator==(const Point& other) const 
        {
            return x == other.x && y == other.y;
        }

        bool operator<(const Point& other) const 
        {
            if (x != other.x) 
                return x < other.x;
            return y < other.y;
        }
    };
}

#endif
