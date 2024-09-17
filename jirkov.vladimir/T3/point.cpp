#include "point.hpp"
#include <iostream>

std::istream& jirkov::operator>>(std::istream& is, Point& value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  StreamGuard StreamGuard(is);
  Point point;
  is >> Del{'('} >> point.x >> Del{';'} >> point.y >> Del{')'};
  if(is)
  {
    value = point;
  }
  return is;
}

std::ostream& jirkov::operator<<(std::ostream& out, const Point& value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << value.x << " " << value.y;
  return out;
}
