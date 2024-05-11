#include "polygonFunctions.hpp"
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>

double ponomarev::getArea(const Polygon & polygon)
{
  std::vector< int > values(polygon.points.size());

  std::transform(
  ++polygon.points.cbegin(),
  polygon.points.cend(),
  polygon.points.cbegin(),
  values.begin(),
  getValue
  );

  values.push_back(getValue(polygon.points.front(), polygon.points.back()));
  int area = std::accumulate(values.cbegin(), values.cend(), 0);
  return abs(area) / 2.0;
}

int ponomarev::getValue(const Point & first, const Point & second)
{
  return (first.x * second.y) - (first.y * second.x);
}

double ponomarev::sumEven(double res, const Polygon & polygon)
{
  return (isEven(polygon)) ? res + getArea(polygon) : res;
}

double ponomarev::sumOdd(double res, const Polygon & polygon)
{
  return (isOdd(polygon)) ? res + getArea(polygon) : res;
}

double ponomarev::sumAll(double res, const Polygon & polygon)
{
  return res + getArea(polygon);
}

double ponomarev::sumIfNumOfVertexes(double res, const Polygon & polygon, size_t numOfVertexes)
{
  return (isEqually(polygon, numOfVertexes)) ? res + getArea(polygon) : res;
}

int ponomarev::getNumOfVertexes(const Polygon & polygon)
{
  return polygon.points.size();
}

bool ponomarev::isEven(const Polygon polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool ponomarev::isOdd(const Polygon polygon)
{
  return (polygon.points.size() % 2 != 0);
}

bool ponomarev::isEqually(const Polygon polygon, size_t numOfVertexes)
{
  return polygon.points.size() == numOfVertexes;
}

bool ponomarev::isRect(const Polygon polygon)
{
  if (polygon.points.size() != 4)
  {
    return false;
  }

  Point a = polygon.points[0];
  Point b = polygon.points[1];
  Point c = polygon.points[2];
  Point d = polygon.points[3];
  return isOrthogonal(a, b, c) && isOrthogonal(b, c, d) && isOrthogonal(c, d, a);
}

bool ponomarev::isOrthogonal(Point a, Point b, Point c)
{
  return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}
