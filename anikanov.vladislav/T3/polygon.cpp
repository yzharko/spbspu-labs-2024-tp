#include "polygon.hpp"
#include <cmath>
#include <numeric>
#include <iostream>
#include <limits>
#include <inDelim.hpp>

anikanov::Polygon &anikanov::Polygon::operator=(const anikanov::Polygon &polygon)
{
  points = polygon.points;
  return *this;
}

size_t anikanov::Polygon::operator%(const size_t number) const
{
  return points.size() % number;
}

anikanov::Point &anikanov::Polygon::operator[](size_t index)
{
  return points[index];
}

const anikanov::Point &anikanov::Polygon::operator[](size_t index) const
{
  return points[index];
}

size_t anikanov::Polygon::getSize() const
{
  return points.size();
}

std::istream &anikanov::operator>>(std::istream &in, anikanov::Polygon &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  dest.points.clear();

  size_t size;

  if (!(in >> size) || size < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  for (size_t i = 0; i < size; ++i) {
    int x, y;

    if (!(in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' })) {
      in.setstate(std::ios::failbit);
      return in;
    }

    Point p{x, y};

    dest.points.push_back(p);
  }

  if (dest.getSize() != size) {
    in.setstate(std::ios::failbit);
  }

  return in;
}

double anikanov::Polygon::areaHelper(const anikanov::Point &point1, const anikanov::Point &point2) const
{
  return (point1.x * point2.y - point1.y * point2.x);
}

double anikanov::Polygon::getArea() const
{
  auto pointTemp = ++points.begin();
  double area = std::accumulate(points.begin(), --points.end(), 0.0,
                                [&pointTemp, this](double areaTemp, const Point &point) {
                                  areaTemp += areaHelper(point, *pointTemp);
                                  pointTemp++;
                                  return areaTemp;
                                });
  area += areaHelper(*--points.end(), *points.begin());
  return std::fabs(area / 2.0);
}
