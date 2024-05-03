#include "internalFuncs.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

double psarev::getArea(Polygon& poly)
{
  std::vector< int > interValues(poly.points.size());
  using namespace std::placeholders;

  std::transform(++(poly.points.begin()), poly.points.end(), poly.points.begin(), interValues.begin(), std::bind(getInterValue, _1, _2));
  int area = std::accumulate(interValues.begin(), interValues.end(), 0);
  double result = abs(area) / 2.0;
  return result;
}

int psarev::getInterValue(Point& ptOne, Point& ptTwo)
{
  return (ptOne.x * ptTwo.y) - (ptOne.y * ptTwo.x);
}

size_t psarev::getNumVerts(Polygon& poly)
{
  return poly.points.size();
}

size_t psarev::getOddVerts(size_t summed, Polygon& poly)
{
  if (poly.points.size() % 2 != 0)
  {
    return ++summed;
  }
  else
  {
    return summed;
  }
}

size_t psarev::getEvenVerts(size_t summed, Polygon& poly)
{
  if (poly.points.size() % 2 == 0)
  {
    return ++summed;
  }
  else
  {
    return summed;
  }
}

size_t psarev::getSpecVerts(size_t summed, Polygon& poly, size_t& numVerts)
{
  if (poly.points.size() == numVerts)
  {
    return ++summed;
  }
  else
  {
    return summed;
  }
}

bool psarev::isDigit(const std::string& str)
{
  for (char c : str)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return !str.empty();
}

bool psarev::isRect(Polygon& poly)
{
  int confCred = 0;
  if (poly.points.size() == 4)
  {
    int x1 = poly.points[0].x;
    int y1 = poly.points[0].y;
    int x2 = poly.points[1].x;
    int y2 = poly.points[1].y;
    int x3 = poly.points[2].x;
    int y3 = poly.points[2].y;
    int x4 = poly.points[3].x;
    int y4 = poly.points[3].y;

    if ((x1 != x2 != x3 != x4) && (y1 != y2 != y3 != y4))
    {
      confCred++;
    }

    Point vecA = { x2 - x1, y2 - y1 };
    Point vecB = { x3 - x2, y3 - y2 };
    Point vecC = { x4 - x3, y4 - y3 };
    Point vecD = { x1 - x4, y2 - y1 };

    if ((vecA.x * vecB.x + vecA.y * vecB.y) == 0 && (vecC.x * vecD.x + vecC.y * vecD.y) == 0)
    {
      confCred++;
    }

    double lenA = sqrt((pow(x2 - x1, 2) + pow(y2 - y1, 2)));
    double lenB = sqrt((pow(x3 - x2, 2) + pow(y3 - y2, 2)));
    double lenC = sqrt((pow(x4 - x3, 2) + pow(y4 - y3, 2)));
    double lenD = sqrt((pow(x1 - x4, 2) + pow(y1 - y4, 2)));

    if ((lenA == lenC) && (lenB == lenD))
    {
      confCred++;
    }
  }

  return confCred == 3 ? true : false;
}

double psarev::plusArea(double summed, Polygon& poly)
{
  return getArea(poly) + summed;
}

double psarev::plusEvenArea(double summed, Polygon& poly)
{
  if (poly.points.size() % 2 == 0)
  {
    return getArea(poly) + summed;
  }
  else
  {
    return summed;
  }
}

double psarev::plusOddArea(double summed, Polygon& poly)
{
  if (poly.points.size() % 2 != 0)
  {
    return getArea(poly) + summed;
  }
  else
  {
    return summed;
  }
}

double psarev::plusSameArea(double summed, Polygon& poly, size_t& numVerts)
{
  if (poly.points.size() == numVerts)
  {
    return getArea(poly) + summed;
  }
  else
  {
    return summed;
  }
}

size_t psarev::getRects(size_t summed, Polygon& poly)
{
  if (isRect(poly))
  {
    return ++summed;
  }
  else
  {
    return summed;
  }
}
