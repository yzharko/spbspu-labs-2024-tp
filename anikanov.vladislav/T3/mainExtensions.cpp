#include "mainExtensions.hpp"

#include <fstream>
#include <limits>
//#include <stdexcept>
#include <algorithm>
#include "vector"
#include "polygon.hpp"

using polygonArr = std::vector< anikanov::Polygon >;
using funcShema = std::function< bool(const anikanov::Polygon &) >;

std::vector< anikanov::Polygon > anikanov::readPolygons(const std::string &filename)
{
  std::vector< Polygon > polygons;
  std::ifstream input(filename);

  if (!input.is_open()) {
    throw std::runtime_error("Unable to open file");
  }

  while (!input.eof()) {
    Polygon polygon;
    input >> polygon;
    if (!input.fail()) {
      polygons.push_back(polygon);
    } else {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return polygons;
}

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
