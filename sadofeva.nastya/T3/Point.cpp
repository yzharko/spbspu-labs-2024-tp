#include "Point.hpp"
#include "datastruct.hpp"
#include "delimiter.hpp"

std::istream& sadofeva::operator>>(std::istream& is, Point& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  iofmtguard fmtguard(is);
  Point point;
  is >> DelimiterIO{'('} >> point.x >> DelimiterIO{';'} >> point.y >> DelimiterIO{')'};
  if (is)
  {
    value = point;
  }
  return is;
}

std::ostream& sadofeva::operator<<(std::ostream& out, const Point& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << value.x << " " << value.y;
  return out;
}

std::istream& sadofeva::operator>>(std::istream& is, Polygon& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  Polygon polygon;
  size_t numOfpoints = 0;
  is >> numOfpoints;
  if (!is || numOfpoints < 3)
  {
    is.setstate(std::ios::failbit);
    return is;
  }
  using inpIter = std::istream_iterator< sadofeva::Point >;
  polygon.point.reserve(numOfpoints);
  std::copy_n(inpIter(is, numOfpoints, std::back_inserter(polygon.point));
  if (is)
  {
    value.point.swap(polygon.point);
  }
  return is;
}

std::ostream& sadofeva::operator<<(std::ostream& out, const Polygon& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  size_t coutOfpoints = value.point.size();
  using osIt = std::ostream_iterator< Point >;
  iofmtguard fmtguard(out);
  out << coutOfpoints;
  std::copy_n(value.point.begin(), coutOfpoints - 1, osIt(out << ' ', " "));
  return out;
}
