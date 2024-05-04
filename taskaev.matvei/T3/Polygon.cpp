#include "Polygon.hpp"
#include "delimeterI.hpp"
#include <iostream>

namespace taskaev
{
  std::istream& operator>>(std::istream& in, Point& point)
  {
    using del = DelimeterI;
    std::istream::sentry guard(in);
    if(!guard)
    {
      return in;
    }
    return in >> del{'('} >> point.x_ >> del{';'} >> point.y_ >> del{')'};
  }

  bool operator<(const Point& left, const Point& right)
  {
    // later
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    //later
  }
}
