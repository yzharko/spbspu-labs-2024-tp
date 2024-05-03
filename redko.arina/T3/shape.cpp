#include "shape.hpp"
#include <functional>
#include <numeric>
#include <algorithm>
#include "delimiter.hpp"

int redko::diffMultPair(const Point & firstP, const Point & secondP)
{
  return firstP.x * secondP.y - firstP.y * secondP.x;
}

bool redko::isPointInTriangle(const Point & point, const Point & firstP, const Point & secondP, const Point & thirdP)
{
  int betweenFS = (firstP.x - point.x) * (secondP.y - firstP.y) - (secondP.x - firstP.x) * (firstP.y - point.y);
  int betweenST = (secondP.x - point.x) * (thirdP.y - secondP.y) - (thirdP.x - secondP.x) * (secondP.y - point.y);
  int betweenTF = (thirdP.x - point.x) * (firstP.y - thirdP.y) - (firstP.x - thirdP.x) * (thirdP.y - point.y);
  return (betweenFS >= 0 && betweenST >= 0 && betweenTF >= 0) || (betweenFS <= 0 && betweenST <= 0 && betweenTF <= 0);
}

bool redko::isRightAngle(const Point & firstP, const Point & secondP, const Point & thirdP)
{
  return ((secondP.x - firstP.x) * (thirdP.x - firstP.x) + (secondP.y - firstP.y) * (thirdP.y - firstP.y) == 0);
}

std::istream & redko::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  int x = 0;
  int y = 0;
  in >> DelimiterIO{ '(' } >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };
  if (in)
  {
    dest.x = x;
    dest.y = y;
  }
  return in;
}

using namespace std::placeholders;

double redko::countArea(const Polygon & shape)
{
  std::vector< int > pairs(shape.points.size());
  std::transform(++shape.points.cbegin(), shape.points.cend(), shape.points.cbegin(), pairs.begin(), std::bind(diffMultPair, _1, _2));
  int area = std::accumulate(pairs.cbegin(), pairs.cend(), 0);
  return abs(area) / 2.0;
}

double redko::sumAreas(double res, const Polygon & shape)
{
  return res + countArea(shape);
}

double redko::sumAreasIfEven(double res, const Polygon & shape)
{
  return (shape.points.size() % 2 == 0) ? res + countArea(shape) : res;
}

double redko::sumAreasIfOdd(double res, const Polygon & shape)
{
  return (shape.points.size() % 2 != 0) ? res + countArea(shape) : res;
}

double redko::sumAreasIfEqual(double res, const Polygon & shape, size_t numOfVertexes)
{
  return (shape.points.size() == numOfVertexes) ? res + countArea(shape) : res;
}

int redko::getNumOfVertexes(const Polygon & shape)
{
  return shape.points.size();
}

bool redko::isNumOfVertexesEven(const Polygon shape)
{
  return shape.points.size() % 2 == 0;
}

bool redko::isNumOfVertexesOdd(const Polygon shape)
{
  return shape.points.size() % 2 != 0;
}

bool redko::isNumOfVertexesEqual(const Polygon shape, size_t numOfVertexes)
{
  return shape.points.size() == numOfVertexes;
}

bool redko::isIntersected(const Polygon & firstS, const Polygon & secondS)
{
  for (size_t i = 0; i < firstS.points.size(); ++i)
  {
    for (size_t j = 0; j < secondS.points.size() - 2; ++j)
    {
      if (isPointInTriangle(firstS.points[i], secondS.points[j], secondS.points[j + 1], secondS.points[j + 2]))
      {
        return true;
      }
    }
  }
  return false;
}

bool redko::isRightShape(const Polygon & shape)
{
  int verts = shape.points.size();
  Point secondP = shape.points[verts - 1];
  Point thirdP = shape.points[verts - 2];
  return std::any_of(shape.points.cbegin() + 2, shape.points.cend(), std::bind(isRightAngle, _1, secondP, thirdP));
}

std::istream & redko::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointCount = 0;
  in >> pointCount;
  Point point{};
  std::vector< Point > polygon{};
  for (size_t i = 0; i < pointCount; ++i)
  {
    in >> point;
    polygon.push_back(point);
  }
  if (in)
  {
    dest = Polygon{ polygon };
  }
  return in;
}
