#ifndef MAINEXTENSIONS_HPP
#define MAINEXTENSIONS_HPP

#include "vector"
#include "polygon.hpp"

namespace anikanov {
  std::vector< double > getAreas(const std::vector< Polygon > &polygons);
  std::vector< double > getAreasIf(const std::vector< Polygon > &polygons, bool (*func)(const Polygon &));
  std::vector< double > getVertexes(const std::vector< Polygon > &polygons);
}

#endif
