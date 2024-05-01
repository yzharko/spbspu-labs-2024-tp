#include "geometry.hpp"
#include "delimiters.hpp"

std::istream& miheev::operator>>(std::istream& in, Point& rhs)
{
  using del = miheev::DelimiterIO;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> del{'('} >> rhs.x >> del{';'} >> rhs.y >> del{')'};
}

std::istream& miheev::operator>>(std::istream& in, Polygon& rhs)
{
  using del = miheev::DelimiterIO;
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t pointsAmount = 0;
  in >> pointsAmount;
  for (size_t i = 0; i < pointsAmount; i++)
  {
    Point temp{};
    in >> temp;
    rhs.points.push_back(temp);
  }
  return in;
}