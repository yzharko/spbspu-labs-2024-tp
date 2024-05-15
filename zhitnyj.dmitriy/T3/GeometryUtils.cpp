#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include <stdexcept>
#include "GeometryUtils.hpp"

double calculateArea(const Polygon& polygon)
{
  int n = polygon.points.size();

  if (n < 3)
  {
    return 0.0;
  }

  std::vector< double > areaComponents(n);

  std::transform(polygon.points.begin(),
    polygon.points.end() - 1,
    polygon.points.begin() + 1,
    areaComponents.begin(),
    [](const Point& a, const Point& b)
    {
      return a.x * b.y - b.x * a.y;
    });

  areaComponents.push_back(
    polygon.points.back().x * polygon.points.front().y - polygon.points.front().x * polygon.points.back().y);

  double area = std::accumulate(areaComponents.begin(), areaComponents.end(), 0.0);

  return std::abs(area) / 2.0;
}

double calculateAreaEvenOdd(bool even, const std::vector< Polygon >& polygons)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.begin(), polygons.end(), areas.begin(), [even](const Polygon& polygon)
  {
    return (polygon.points.size() % 2 == 0) == even ? calculateArea(polygon) : 0.0;
  });
  return std::reduce(areas.begin(), areas.end(), 0.0);
}

double calculateMeanArea(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }

  std::vector< double > areas(polygons.size());
  std::transform(polygons.begin(), polygons.end(), areas.begin(), calculateArea);

  double totalArea = std::reduce(areas.begin(), areas.end(), 0.0);
  return totalArea / polygons.size();
}

double calculateAreaByVertexCount(int count, const std::vector< Polygon >& polygons)
{
  std::vector< double > areas(polygons.size());
  std::transform(polygons.begin(), polygons.end(), areas.begin(), [count](const Polygon& polygon)
  {
    return polygon.points.size() == static_cast< std::vector< Point >::size_type >(count) ? calculateArea(polygon)
                                                                                          : 0.0;
  });
  return std::reduce(areas.begin(), areas.end(), 0.0);
}

double calculateMaxArea(const std::vector< Polygon >& polygons)
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return calculateArea(a) < calculateArea(b);
  });
  return maxElement != polygons.end() ? calculateArea(*maxElement) : 0.0;
}

int calculateMaxVertexes(const std::vector< Polygon >& polygons)
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return maxElement != polygons.end() ? maxElement->points.size() : 0;
}

double calculateMinArea(const std::vector< Polygon >& polygons)
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return calculateArea(a) < calculateArea(b);
  });
  return minElement != polygons.end() ? calculateArea(*minElement) : 0.0;
}

int calculateMinVertexes(const std::vector< Polygon >& polygons)
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return minElement != polygons.end() ? minElement->points.size() : 0;
}

int countPolygons(bool even, const std::vector< Polygon >& polygons, int vertex_count)
{
  if (vertex_count != 0)
  {
    return std::count_if(polygons.begin(), polygons.end(), [vertex_count](const Polygon& polygon)
    {
      return polygon.points.size() == static_cast< std::vector< Point >::size_type >(vertex_count);
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

int countPerms(const Polygon& target, const std::vector< Polygon >& polygons)
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

int removeEcho(const Polygon& target, std::vector< Polygon >& polygons)
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
