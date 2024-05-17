#include "mainExtensions.hpp"

#include "vector"
#include "polygon.hpp"

using polygonArr = std::vector< anikanov::Polygon >;

std::vector< double > getAreas(const polygonArr &polygons)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    areas.push_back(polygon.getArea());
  }
  return areas;
}

std::vector< double > getAreasIf(const polygonArr &polygons, bool (*func)(const anikanov::Polygon &))
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    if (func(polygon)) {
      areas.push_back(polygon.getArea());
    }
  }
  return areas;
}

std::vector< double > getVertexes(const polygonArr &polygons)
{
  std::vector< double > vertexes;
  for (const auto &polygon: polygons) {
    vertexes.push_back(polygon.getSize());
  }
  return vertexes;
}
