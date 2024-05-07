#include "predicates.hpp"
#include <algorithm>

bool tellez::hasEvenVertexesCount(const Polygon& rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool tellez::hasOddVertexesCount(const Polygon& rhs)
{
  return !hasEvenVertexesCount(rhs);
}

bool tellez::vertexesCount(const Polygon& rhs, std::size_t num)
{
  return rhs.points.size() == num;
}

bool tellez::compareAreas(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool tellez::compareVertexes(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool tellez::comparePointsX(const Point& lhs, const Point& rhs)
{
  return lhs.x < rhs.x;
}

bool tellez::comparePointsY(const Point& lhs, const Point& rhs)
{
  return lhs.y < rhs.y;
}

bool tellez::comparePolygonsMinX(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsX);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsX(*lhs_min, *rhs_min);
}

bool tellez::comparePolygonsMinY(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsY);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsY(*lhs_min, *rhs_min);
}

bool tellez::comparePolygonsMaxX(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsX);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsX);

  return comparePointsX(*lhs_max, *rhs_max);
}

bool tellez::comparePolygonsMaxY(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), comparePointsY);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), comparePointsY);

  return comparePointsY(*lhs_max, *rhs_max);
}
