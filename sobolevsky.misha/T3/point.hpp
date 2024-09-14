#ifndef POINT_HPP
#define POINT_HPP

#include <fstream>

namespace sobolevsky
{
  struct Point
  {
    int x, y;
  };

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, Point& point);
}

#endif
