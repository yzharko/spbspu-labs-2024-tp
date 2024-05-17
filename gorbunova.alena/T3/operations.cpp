#include <map>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include "operations.hpp"

using namespace std::placeholders;

double gorbunova::sumAreas(const std::vector< Polygon > &polygons)
{
  std::vector< double > AreasOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon &polygon)
    {
      return getArea(polygon);
    });

  double sumOfAreas = std::accumulate(
    AreasOfPolygons.begin(),
    AreasOfPolygons.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2));
  return sumOfAreas;
}

void gorbunova::areaOdd(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > onlyOddPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyOddPolygons),
    [](const Polygon &polygon)
    {
      return (polygon.points.size() % 2);
    });
  double sum = sumAreas(onlyOddPolygons);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void gorbunova::areaEven(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > onlyEvenPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyEvenPolygons),
    [](const Polygon &polygon)
    {
      return !(polygon.points.size() % 2);
    });
  double sum = sumAreas(onlyEvenPolygons);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void gorbunova::areaMean(const std::vector< Polygon > &polygons, std::ostream &out)
{
  double sum = sumAreas(polygons);
  if (polygons.empty())
  {
    throw std::out_of_range("");
  }
  out << std::setprecision(1) << std::fixed << sum / polygons.size() << '\n';
}

void gorbunova::areaNumOfVertexes(size_t vertexes, const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > polygonsWithNVertexes;
  auto OnlyNVertexes = std::bind(std::equal_to< size_t >{}, vertexes, _1);
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [OnlyNVertexes](const Polygon &polygon)
    {
      return OnlyNVertexes(polygon.points.size());
    });

  double sum = sumAreas(polygonsWithNVertexes);
  std::vector< size_t > isVertexesExist;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(isVertexesExist),
    [vertexes](const Polygon &polygon)
    {
      return polygon.points.size() == vertexes;
    });
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

double gorbunova::getArea(const Polygon &polygon)
{
  std::vector< double > sumOfCoords;
  std::transform(
    polygon.points.begin(),
    polygon.points.end() - 1,
    std::next(polygon.points.begin()),
    std::back_inserter(sumOfCoords),
    [](const Point &a, const Point &b)
    {
      return a.x * b.y;
    });

  std::vector< double > diffOfCoords;
  std::transform(
    polygon.points.begin(),
    polygon.points.end() - 1,
    std::next(polygon.points.begin()),
    std::back_inserter(diffOfCoords),
    [](const Point &a, const Point &b)
    {
      return a.y * b.x;
    });

  double sum = std::accumulate(
    sumOfCoords.begin(),
    sumOfCoords.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2));
  double diff = std::accumulate(
    diffOfCoords.begin(),
    diffOfCoords.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2));
  return 0.5 * std::abs(sum + polygon.points.back().x * polygon.points.front().y - diff - polygon.points.front().x * polygon.points.back().y);
}

void gorbunova::maxArea(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< double > AreasOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon &polygon)
    {
      return getArea(polygon);
    });
  std::sort(AreasOfPolygons.begin(), AreasOfPolygons.end());
  if (AreasOfPolygons.empty())
  {
    throw std::out_of_range("");
  }
  out << std::setprecision(1) << std::fixed << AreasOfPolygons.back() << '\n';
}

void gorbunova::maxVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< size_t > vertexesOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons),
    [](const Polygon &polygon)
    {
      return polygon.points.size();
    });
  std::sort(vertexesOfPolygons.begin(), vertexesOfPolygons.end());
  if (vertexesOfPolygons.empty())
  {
    throw std::out_of_range("");
  }
  out << vertexesOfPolygons.back() << '\n';
}

void gorbunova::minArea(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< double > AreasOfPolygons;
  std::transform(polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon &polygon)
    { return getArea(polygon); });
  std::sort(AreasOfPolygons.begin(), AreasOfPolygons.end());
  out << std::setprecision(1) << std::fixed << AreasOfPolygons.front() << '\n';
}

void gorbunova::minVertexes(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< size_t > vertexesOfPolygons;
  std::transform(polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons),
    [](const Polygon &polygon)
    { return polygon.points.size(); });
  std::sort(vertexesOfPolygons.begin(), vertexesOfPolygons.end());
  out << vertexesOfPolygons.front() << '\n';
}

void gorbunova::countEven(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > onlyEvenPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyEvenPolygons),
    [](const Polygon &polygon)
    {
      return !(polygon.points.size() % 2);
    });
  out << onlyEvenPolygons.size() << '\n';
}

void gorbunova::countOdd(const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > onlyOddPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyOddPolygons),
    [](const Polygon &polygon)
    {
      return (polygon.points.size() % 2);
    });
  out << onlyOddPolygons.size() << '\n';
}

void gorbunova::countNumOfVertexes(size_t vertexes, const std::vector< Polygon > &polygons, std::ostream &out)
{
  std::vector< Polygon > polygonsWithNVertexes;
  auto OnlyNVertexes = std::bind(std::equal_to< size_t >{}, vertexes, _1);
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [OnlyNVertexes](const Polygon &polygon)
    {
      return OnlyNVertexes(polygon.points.size());
    });
  out << polygonsWithNVertexes.size() << '\n';
}

bool gorbunova::checkPerms(const Polygon &lhs, const Polygon &rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  auto isPointInPolygon = std::bind(isPointInShape, lhs, _1);
  size_t countPointsIn = std::count_if(rhs.points.begin(), rhs.points.end(), isPointInPolygon);
  return lhs.points.size() == countPointsIn;
}

bool gorbunova::isPointInShape(const Polygon &toCompare, const Point &point)
{
  return std::find_if(
    toCompare.points.begin(),
    toCompare.points.end(),
    [point](const Point &pointToCompare)
    {
      return (pointToCompare.x == point.x && pointToCompare.y == point.y) || (pointToCompare.x == point.y && pointToCompare.y == point.x);
    }) != toCompare.points.end();
}

void gorbunova::updateFrame(const Point &point, Point &topLeft, Point &bottomRight)
{
  topLeft.x = std::min(topLeft.x, point.x);
  topLeft.y = std::max(topLeft.y, point.y);
  bottomRight.x = std::max(bottomRight.x, point.x);
  bottomRight.y = std::min(bottomRight.y, point.y);
}

bool gorbunova::pointInFrame(const Point &point, const Point &topLeft, const Point &bottomRight)
{
  return (point.x >= topLeft.x && point.x <= bottomRight.x && point.y <= topLeft.y && point.y >= bottomRight.y);
}
