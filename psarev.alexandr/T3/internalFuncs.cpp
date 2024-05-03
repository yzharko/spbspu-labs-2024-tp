#include "internalFuncs.hpp"
#include <algorithm>
#include <functional>
#include <numeric>

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

double psarev::plusSameArea(double summed, Polygon& poly, size_t numOfVerts)
{
  if (poly.points.size() == numOfVerts)
  {
    return getArea(poly) + summed;
  }
  else
  {
    return summed;
  }
}
