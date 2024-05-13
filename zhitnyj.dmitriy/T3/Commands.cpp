#include <algorithm>
#include <numeric>
#include <iterator>
#include "Commands.hpp"
#include "GeometryUtils.hpp"

double Commands::calculateAreaEvenOdd(const std::vector< Polygon >& polygons, bool even) const
{
  auto isEvenOdd = [even](const Polygon& polygon)
  {
    return (polygon.points.size() % 2 == 0) == even;
  };
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double sum, const Polygon& polygon)
  {
    return sum + (isEvenOdd(polygon) ? GeometryUtils().calculateArea(polygon) : 0.0);
  });
}

double Commands::calculateMeanArea(const std::vector< Polygon >& polygons) const
{
  double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double sum, const Polygon& polygon)
  {
    return sum + GeometryUtils().calculateArea(polygon);
  });
  return polygons.empty() ? 0.0 : totalArea / polygons.size();
}

double Commands::calculateAreaByVertexCount(const std::vector< Polygon >& polygons, int count) const
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [count](double sum, const Polygon& polygon)
      {
        return sum + (polygon.points.size() == count ? GeometryUtils().calculateArea(polygon) : 0.0);
      });
}

double Commands::calculateMaxArea(const std::vector< Polygon >& polygons) const
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return GeometryUtils().calculateArea(a) < GeometryUtils().calculateArea(b);
  });
  return maxElement != polygons.end() ? GeometryUtils().calculateArea(*maxElement) : 0.0;
}

int Commands::calculateMaxVertexes(const std::vector< Polygon >& polygons) const
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return maxElement != polygons.end() ? maxElement->points.size() : 0;
}

double Commands::calculateMinArea(const std::vector< Polygon >& polygons) const
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return GeometryUtils().calculateArea(a) < GeometryUtils().calculateArea(b);
  });
  return minElement != polygons.end() ? GeometryUtils().calculateArea(*minElement) : 0.0;
}

int Commands::calculateMinVertexes(const std::vector< Polygon >& polygons) const
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return minElement != polygons.end() ? minElement->points.size() : 0;
}

int Commands::countPolygons(const std::vector< Polygon >& polygons, bool even, int vertex_count) const
{
  if (vertex_count != -1)
  {
    return std::count_if(polygons.begin(), polygons.end(), [vertex_count](const Polygon& polygon)
    {
      return polygon.points.size() == static_cast<std::vector< Point >::size_type>(vertex_count);
    });
  }
  else
  {
    return std::count_if(polygons.begin(), polygons.end(), [even](const Polygon& polygon)
    {
      return (polygon.points.size() % 2 == 0) == even;
    });
  }
}

int Commands::countPerms(const std::vector< Polygon >& polygons, const Polygon& target) const
{
  auto arePermutations = [](const std::vector< Point >& a, const std::vector< Point >& b)
  {
    if (a.size() != b.size())
    {
      return false;
    }

    std::vector< Point > sortedA = a;
    std::vector< Point > sortedB = b;

    auto pointComp = [](const Point& p1, const Point& p2)
    {
      return (p1.x == p2.x) ? (p1.y < p2.y) : (p1.x < p2.x);
    };

    std::sort(sortedA.begin(), sortedA.end(), pointComp);
    std::sort(sortedB.begin(), sortedB.end(), pointComp);

    auto comparePoints = [](const Point& a, const Point& b)
    {
      return (a.x == b.x && a.y == b.y) || (a.x == b.y && a.y == b.x);
    };

    return std::equal(sortedA.begin(), sortedA.end(), sortedB.begin(), comparePoints);
  };

  return std::count_if(polygons.begin(), polygons.end(), [&](const Polygon& polygon)
  {
    return arePermutations(polygon.points, target.points);
  });
}

int Commands::removeEcho(std::vector< Polygon >& polygons, const Polygon& target) const
{
  auto isDuplicate = [&](const Polygon& a, const Polygon& b)
  {
    return a == b && a == target;
  };

  auto removeIt = std::unique(polygons.begin(), polygons.end(), isDuplicate);
  int removeCount = std::distance(removeIt, polygons.end());
  polygons.erase(removeIt, polygons.end());
  return removeCount;
}
