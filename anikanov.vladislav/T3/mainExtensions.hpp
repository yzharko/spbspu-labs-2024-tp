#ifndef MAINEXTENSIONS_HPP
#define MAINEXTENSIONS_HPP

#include <functional>
#include "vector"
#include "polygon.hpp"

namespace anikanov {
  std::vector< double > getAreas(const std::vector< Polygon > &polygons);
  std::vector< double > getAreasIf(const std::vector< Polygon > &polygons, std::function< bool(const Polygon &) >);
  std::vector< size_t > getVertexes(const std::vector< Polygon > &polygons);
}

#endif
