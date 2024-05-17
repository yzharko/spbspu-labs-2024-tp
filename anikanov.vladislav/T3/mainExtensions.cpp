#include "mainExtensions.hpp"

#include "vector"
#include "polygon.hpp"

using polygonArr = std::vector< anikanov::Polygon >;
using funcShema = std::function< bool(const anikanov::Polygon &) >;

std::vector< double > anikanov::getAreas(const polygonArr &polygons)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    areas.push_back(polygon.getArea());
  }
  return areas;
}

std::vector< double > anikanov::getAreasIf(const polygonArr &polygons, funcShema func)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    if (func(polygon)) {
      areas.push_back(polygon.getArea());
    }
  }
  return areas;
}

std::vector< size_t > anikanov::getVertexes(const polygonArr &polygons)
{
  std::vector< size_t > vertexes;
  for (const auto &polygon: polygons) {
    vertexes.push_back(polygon.getSize());
  }
  return vertexes;
}
