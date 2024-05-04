#include "shape.hpp"
#include <functional>
#include <numeric>
#include <algorithm>
#include "delimiter.hpp"

int redko::diffMultPair(const Point & firstP, const Point & secondP)
{
  return firstP.x * secondP.y - firstP.y * secondP.x;
}

redko::Point redko::makeVector(const Point & firstP, const Point & secondP)
{
  Point vector{};
  vector.x = secondP.x - firstP.x;
  vector.y = secondP.y - firstP.y;
  return vector;
}

int redko::makeScalar(const Point & firstV, const Point & secondV)
{
  return firstV.x * secondV.x + firstV.y * secondV.y;
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

int redko::makeVectorMultiply(const Point & point, const Point & firstP, const Point & secondP)
{
  return (firstP.x - point.x) * (secondP.y - firstP.y) - (secondP.x - firstP.x) * (firstP.y - point.y);
}

bool redko::isPointInPolygon(const Point & point, const Polygon & shape)
{
  std::vector< int > vectorProduct(shape.points.size() - 1);
  std::transform(
    ++shape.points.cbegin(),
    shape.points.cend(),
    shape.points.cbegin(),
    vectorProduct.begin(),
    std::bind(makeVectorMultiply, point, _2, _1)
  );
  vectorProduct.push_back(makeVectorMultiply(point, shape.points.back(), shape.points.front()));
  bool pointIsToTheRight = std::all_of(
    vectorProduct.cbegin(),
    vectorProduct.cend(),
    [](int num)
    {
      return num >= 0;
    }
  );
  bool pointIsToTheLeft = std::all_of(
    vectorProduct.cbegin(),
    vectorProduct.cend(),
    [](int num)
    {
      return num <= 0;
    }
  );
  return pointIsToTheRight || pointIsToTheLeft;
}

bool redko::isIntersected(const Polygon & firstS, const Polygon & secondS)
{
  bool firstInSecond = std::any_of(
    firstS.points.cbegin(),
    firstS.points.cend(),
    std::bind(isPointInPolygon, _1, secondS)
  );
  bool secondInFirst = std::any_of(
    secondS.points.cbegin(),
    secondS.points.cend(),
    std::bind(isPointInPolygon, _1, firstS)
  );
  return firstInSecond || secondInFirst;
}

bool redko::isEqual(int firstN, int secondN)
{
  return firstN == secondN;
}

bool redko::isRightShape(const Polygon & shape)
{
  std::vector< Point > vectors(shape.points.size() - 1);
  std::transform(
    ++shape.points.cbegin(),
    shape.points.cend(), shape.points.cbegin(),
    vectors.begin(),
    std::bind(makeVector, _1, _2)
  );
  vectors.push_back(makeVector(shape.points.back(), shape.points.front()));

  std::vector< int > scalars(vectors.size() - 1);
  std::transform(
    ++vectors.cbegin(),
    vectors.cend(),
    vectors.cbegin(),
    scalars.begin(),
    std::bind(makeScalar, _1, _2)
  );
  scalars.push_back(makeScalar(vectors.back(), vectors.front()));
  return std::any_of(scalars.cbegin(), scalars.cend(), std::bind(isEqual, _1, 0));
}

std::istream & redko::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointCount = 0;
  if (!(in >> pointCount) || pointCount <= 2)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > polygon;
  Point point;
  for (size_t i = 0; i < pointCount; ++i)
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (in >> point)
    {
      polygon.push_back(point);
    }
  }
  if (in && polygon.size() == pointCount)
  {
    dest = Polygon{ polygon };
  }
  return in;
}
