#include "point.hpp"
#include <iostream>

std::istream& jirkov::operator>>(std::istream& in, Point& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  StreamGuard StreamGuard(in);
  Point point;
  in >> Del{'('} >> value.x >> Del{';'} >> value.y >> Del{')'};
  if (in)
  {
    value = point;
  }
  return in;
}

