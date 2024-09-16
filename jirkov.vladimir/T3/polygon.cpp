#include "polygon.hpp"
#include <iostream>
#include <cstddef>

std::istream& jirkov::operator>>(std::istream& in, Polygon& value)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  StreamGuard StreamGuard(in);
  size_t count = 0;
  Point point;
  Polygon temp;
  in >> count;
  if(!in || count < 3)
  {
    in.setstate(std::ios::failbit);
  }
  for(size_t i = 0; i < count; i++)
  {
    in >> point;
    temp.points.push_back(point);
  }
  if(count != temp.points.size())
  {
    in.setstate(std::ios::failbit);
  }
  if(in)
  {
    value = temp;
  }
  return in;
}
