#include <iostream>
#include "point.hpp"

std::istream& kovshikov::operator>>(std::istream& is, Point& value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  iofmtguard fmtguard(is);
  Point point;
  is >> Del{'('} >> point.x >> Del{';'} >> point.y >> Del{')'};
  if(is)
  {
    value = point;
  }
  return is;
}

std::ostream& kovshikov::operator<<(std::ostream& out, const Point& value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << value.x << " " << value.y;
  return out;
}
