#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

namespace sobolevsky
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& in, sobolevsky::Point& point);
}

#endif
