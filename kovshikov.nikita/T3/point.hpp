#ifndef POINT_HPP
#define POINT_HPP
#include "io_structures.hpp"
#include "scope_guard.hpp"

namespace kovshikov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& is, Point& value);
  std::ostream& operator<<(std::ostream& out, const Point& value);
}

#endif
