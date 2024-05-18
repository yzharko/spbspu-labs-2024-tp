#ifndef POINT_H
#define POINT_H

#include <iosfwd>

namespace anikanov {
  struct Point {
    int x;
    int y;

    Point() : x(0), y(0)
    {
    }
    Point(int x, int y) : x(x), y(y)
    {
    }
    Point &operator=(const Point &point);
  };

  std::istream &operator>>(std::istream &in, Point &dest);
}

#endif
