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
  using input_it_t = std::istream_iterator< reznikova::Point >;
  int size = 0;
  Polygon polygon;
  is >> size;
  std::copy_n(input_it_t(is), size, std::back_inserter(polygon.points));
  is.clear();
  is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if (size <= 2)
  {
    is.setstate(std::ios_base::failbit);
  }
  if (is)
  {
    value = polygon;
  }
  return is;
}
