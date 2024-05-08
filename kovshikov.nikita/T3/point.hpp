#ifndef POINT_HPP
#define POINT_HPP
#include "io_structures.hpp"

namespace kovshikov
{
  struct Point
  {
    int x, y;
  };
  std::istream& operator>>(std::istream& is, Point& value);
}

#endif
