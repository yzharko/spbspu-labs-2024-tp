#ifndef POINT_H
#define POINT_H

#include <iosfwd>

namespace anikanov {
  struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y)
    {
    }
  };
}

#endif
