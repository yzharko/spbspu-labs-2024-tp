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
  int count = 0;
  Point point;
  Polygon temp;
  is >> count;
  for(int i = 0; i < count; i++)
  {
    is >> point;
    temp.points.push_back(point);
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
