#include "predicates.hpp"
#include "polygon.hpp"
#include <algorithm>
#include <vector>

bool tellez::even_vertexes(const Polygon& rhs)
{
  return rhs.points.size() % 2 == 0;
}

bool tellez::odd_vertexes(const Polygon& rhs)
{
  return !even_vertexes(rhs);
}

bool tellez::vertexes_count(const Polygon& rhs, std::size_t num)
{
  return rhs.points.size() == num;
}

bool tellez::compare_areas(const Polygon& lhs, const Polygon& rhs)
{
  return get_area(lhs) < get_area(rhs);
}

bool tellez::compare_vertexes(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

bool tellez::compare_points_x(const Point& lhs, const Point& rhs)
{
  return lhs.x < rhs.x;
}

bool tellez::compare_points_y(const Point& lhs, const Point& rhs)
{
  return lhs.y < rhs.y;
}

bool tellez::compare_polygons_min_x(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), compare_points_x);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), compare_points_x);

  return compare_points_x(*lhs_min, *rhs_min);
}

bool tellez::compare_polygons_min_y(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_min = std::min_element(lhs.points.cbegin(), lhs.points.cend(), compare_points_y);
  auto rhs_min = std::min_element(rhs.points.cbegin(), rhs.points.cend(), compare_points_y);

  return compare_points_y(*lhs_min, *rhs_min);
}

bool tellez::compare_polygons_max_x(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), compare_points_x);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), compare_points_x);

  return compare_points_x(*lhs_max, *rhs_max);
}

bool tellez::compare_polygons_max_y(const Polygon& lhs, const Polygon& rhs)
{
  auto lhs_max = std::max_element(lhs.points.cbegin(), lhs.points.cend(), compare_points_y);
  auto rhs_max = std::max_element(rhs.points.cbegin(), rhs.points.cend(), compare_points_y);

  return compare_points_y(*lhs_max, *rhs_max);
}
