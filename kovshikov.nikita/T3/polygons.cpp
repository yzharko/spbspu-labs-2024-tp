#include "polygons.hpp"
#include <iostream>
#include <cstddef>

std::istream& kovshikov::operator>>(std::istream& is, Polygon& value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  iofmtguard fmtguard(is);
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
    is >> point;
    temp.points.push_back(point);
  }
  char peek = is.peek();
  if(count != temp.points.size() || peek != '\n')
  {
    is.setstate(std::ios::failbit);
  }
  if(is)
  {
    value = temp;
  }
  return is;
}

std::ostream& kovshikov::operator<<(std::ostream& out, const Polygon& value)
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
