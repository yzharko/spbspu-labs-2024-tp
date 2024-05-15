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

bool ponomarev::isOrthogonal(const Point a, const Point b, const Point c)
{
  return (b.x - a.x) * (b.x - c.x) + (b.y - a.y) * (b.y - c.y) == 0;
}

bool ponomarev::isIntersection(const Polygon & first, const Polygon & second)
{
  int firstMaxX = (*std::max_element(first.points.begin(), first.points.end(), whichBiggerX)).x;
  int firstMaxY = (*std::max_element(first.points.begin(), first.points.end(), whichBiggerY)).y;
  int firstMinX = (*std::min_element(first.points.begin(), first.points.end(), whichSmallerX)).x;
  int firstMinY = (*std::min_element(first.points.begin(), first.points.end(), whichSmallerY)).y;
  int secondMaxX = (*std::max_element(second.points.begin(), second.points.end(), whichBiggerX)).x;
  int secondMaxY = (*std::max_element(second.points.begin(), second.points.end(), whichBiggerY)).y;
  int secondMinX = (*std::min_element(second.points.begin(), second.points.end(), whichSmallerX)).x;
  int secondMinY = (*std::min_element(second.points.begin(), second.points.end(), whichSmallerY)).y;

  bool isIntersect = (firstMaxX >= secondMinX) && (firstMaxY >= secondMinY) && (firstMinX <= secondMaxX) && (firstMinY <= secondMaxY);

  return isIntersect;
}

bool ponomarev::whichBiggerX(const Point & first, const Point & second)
{
  return (first.x < second.x);
}

bool ponomarev::whichBiggerY(const Point & first, const Point & second)
{
  return (first.y < second.y);
}

bool ponomarev::whichSmallerX(const Point & first, const Point & second)
{
  return (first.x < second.x);
}

bool ponomarev::whichSmallerY(const Point & first, const Point & second)
{
  return (first.y < second.y);
}
