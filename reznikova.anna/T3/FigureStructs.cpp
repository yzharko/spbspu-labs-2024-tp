#include "FigureStructs.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include <Delimeter.hpp>

std::istream & reznikova::operator>>(std::istream & is, reznikova::Point & value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  Point point;
  is >> del{'('} >> point.x >> del{';'} >> point.y >> del{')'};
  if (is)
  {
    value = point;
  }
  return is;
}

std::istream & reznikova::operator>>(std::istream & is, reznikova::Polygon & value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  size_t size = 0;
  Polygon polygon;
  Point point;
  if (!(is >> size))
  {
    is.setstate(std::ios::failbit);
  }
  for (size_t i = 0; i < size; i++)
  {
    is >> point;
    if (is)
    {
      polygon.points.push_back(point);
    }
  }
  if ((size <= 2) or (polygon.points.size() != size))
  {
    is.setstate(std::ios::failbit);
  }
  if (is)
  {
    value = polygon;
  }
  return is;
}
