#include "polygons.hpp"
#include <cstddef>
#include <iostream>

std::istream& jirkov::operator>>(std::istream& is, Polygon& value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  StreamGuard StreamGuard(is);
  size_t count = 0;
  Point point;
  Polygon temp;
  is >> count;
  if(!is || count < 3)
  {
    is.setstate(std::ios::failbit);
  }
  for(size_t i = 0; i < count; i++)
  {
    if (is.get() == '\n')
    {
      is.setstate(std::ios::failbit);
      return is;
    }
    if(is >> point)
    {
      temp.points.push_back(point);
    }
  }
  if(!is || count != temp.points.size() || is.get() != '\n')
  {
    is.setstate(std::ios::failbit);
  }
  if(is)
  {
    value = temp;
  }
  return is;
}

std::ostream& jirkov::operator<<(std::ostream& out, const Polygon& value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  std::vector< Point >::const_iterator start = value.points.begin();
  std::vector< Point >::const_iterator finish = value.points.end();
  while(start != finish)
  {
    out << *start << "|";
    start++;
  }
  return out;
}
