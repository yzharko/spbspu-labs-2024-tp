#include "FigureStructs.hpp"
#include <algorithm>
#include <iterator>
#include <limits>
#include "Delimeter.hpp"

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
  int size = 0;
  Polygon polygon;
  Point point;
  is >> size;
  if (!is)
  {
    is.setstate(std::ios_base::failbit);
  }
  for (int i = 0; i < size; i++)
  {
    if (is >> point)
    {
      polygon.points.push_back(point);
    }
  }
  is.clear();
  is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (size <= 2 or polygon.points.size() != size_t(size))
  {
    is.setstate(std::ios_base::failbit);
  }
  if (is)
  {
    value = polygon;
  }
  return is;
}
