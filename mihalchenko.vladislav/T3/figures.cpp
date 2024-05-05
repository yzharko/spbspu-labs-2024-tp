#include "figures.hpp"
#include "../common/scopeGuard.hpp"

// #include <iterator>
// #include <iostream>

std::istream &mihalchenko::operator>>(std::istream &is, DelimiterIO &&exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream &mihalchenko::operator>>(std::istream &is, Point &rhs)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  Point input{0, 0};
  using del = DelimiterIO;
  is >> del{'('} >> input.x >> del{';'} >> input.y >> del{')'};
  if (is)
  {
    rhs = input;
  }
  return is;
}

std::ostream &mihalchenko::operator<<(std::ostream &out, const Point &rhs)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  return out << '(' << rhs.x << ';' << rhs.y << ')';
}

std::istream &mihalchenko::operator>>(std::istream &is, Polygon &rhs)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  Polygon polygon;
  size_t counterOfPoints = 0;
  is >> counterOfPoints;
  if (counterOfPoints < 3)
  {
    is.setstate(std::ios::failbit);
  }
  else
  {
    // polygon.points.reserve(counterOfPoints);
    std::copy_n(std::istream_iterator<Point>(is),
                counterOfPoints,
                std::back_inserter(polygon.points));
  }
  if (is)
  {
    rhs.points = polygon.points;
  }
  return is;
}

std::ostream &mihalchenko::operator<<(std::ostream &out, const Polygon &rhs)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  size_t counterOfPoints = rhs.points.size();
  iofmtguard fmtguard(out);
  out << counterOfPoints;
  std::copy_n(rhs.points.begin(),
              counterOfPoints - 1,
              std::ostream_iterator<Point>(out << ' ', " "));
  return out; // << rhs.points.back();
}

/*std::istream &mihalchenko::operator>>(std::istream &is, std::string &rhs)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  std::string rez = "";
  using del = DelimiterIO;
  is >> rez >> del{' '};
  rez += ';';
  is >> rez;
  if (is)
  {
    rhs = rez;
  }
  return is;
}*/

/*bool mihalchenko::operator==(const Polygon& lhs, const Polygon& rhs)
{
  auto firstLhs = lhs.points.begin();
  auto lastLhs = lhs.points.end();
  auto firstRhs = rhs.points.begin();
  auto lastRhs = rhs.points.end();
  bool result = std::equal(firstLhs, lastLhs, firstRhs, lastRhs);
  return result;
}*/
