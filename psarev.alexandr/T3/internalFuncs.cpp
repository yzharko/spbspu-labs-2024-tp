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
  interValues.push_back(getInterValue(poly.points.front(), poly.points.back()));
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

    Point vecA = { x2 - x1, y2 - y1 };
    Point vecB = { x3 - x2, y3 - y2 };
    Point vecC = { x4 - x3, y4 - y3 };
    Point vecD = { x1 - x4, y1 - y4 };

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

  return confCred == 2 ? true : false;
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

psarev::Polygon psarev::makeFrame(std::vector< Polygon >& polyVec)
{
  std::vector< int > maxXCoos(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), maxXCoos.begin(), getMaxX);
  int maxX = *(std::max_element(maxXCoos.begin(), maxXCoos.end()));

  std::vector< int > minXCoos(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), maxXCoos.begin(), getMinX);
  int minX = *(std::max_element(minXCoos.begin(), minXCoos.end()));

  std::vector< int > maxYCoos(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), maxYCoos.begin(), getMaxY);
  int maxY = *(std::max_element(maxYCoos.begin(), maxYCoos.end()));

  std::vector< int > minYCoos(polyVec.size());
  std::transform(polyVec.begin(), polyVec.end(), maxYCoos.begin(), getMinY);
  int minY = *(std::max_element(minYCoos.begin(), minYCoos.end()));

  Polygon frame;
  Point rightUp = { maxX, maxY };
  Point leftDn = { minX, minY };
  frame.points.emplace_back(rightUp);
  frame.points.emplace_back(leftDn);
  return frame;
}

int psarev::getMaxX(Polygon& poly)
{
  std::vector< int > maxCoos(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), maxCoos.begin(), getX);
  int maxX = *(std::max_element(maxCoos.begin(), maxCoos.end()));
  return maxX;
}

int psarev::getMinX(Polygon& poly)
{
  std::vector< int > xCoos(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), xCoos.begin(), getX);
  int minX = *(std::min_element(xCoos.begin(), xCoos.end()));
  return minX;
}

int psarev::getX(Point& pt)
{
  return pt.x;
}

int psarev::getMaxY(Polygon& poly)
{
  std::vector< int > maxCoos(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), maxCoos.begin(), getY);
  int maxY = *(std::max_element(maxCoos.begin(), maxCoos.end()));
  return maxY;
}

int psarev::getMinY(Polygon& poly)
{
  std::vector< int > yCoos(poly.points.size());
  std::transform(poly.points.begin(), poly.points.end(), yCoos.begin(), getY);
  int minY = *(std::min_element(yCoos.begin(), yCoos.end()));
  return minY;
}

int psarev::getY(Point& pt)
{
  return pt.y;
}
