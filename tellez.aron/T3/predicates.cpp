#include "predicates.hpp"

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
