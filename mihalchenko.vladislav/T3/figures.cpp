#include "figures.hpp"
// #include <iostream>
#include <algorithm>
#include <cmath>

/*size_t mihalchenko::getSize(const Polygon &polygon)
{
  return polygon.points.size();
}

double mihalchenko::sumArea(double area, const Point &startPoint)
{
  auto nextPoint = *std::next(&startPoint);
  auto triangleArea = ((startPoint.x * nextPoint.y) - (nextPoint.x * startPoint.y));
  auto newArea = area + triangleArea;
  return newArea;
}

double mihalchenko::countArea(const Polygon &polygon)
{
  double area = std::accumulate(polygon.points.begin(), std::prev(polygon.points.end()), 0., mihalchenko::sumArea);
  auto lhs = std::prev(polygon.points.end())->x * polygon.points.front().y;
  auto rhs = polygon.points.front().x * std::prev(polygon.points.end())->y;
  auto pmArea = lhs - rhs;
  area = 0.5 * std::abs(area + pmArea);
  return area;
}*/

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
