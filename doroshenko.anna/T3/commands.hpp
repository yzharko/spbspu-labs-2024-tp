#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include "polygon.hpp"

namespace doroshenko
{
  void cmdArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void evenArea(const std::vector< Polygon >& polygons, std::ostream& output);
  double plusArea(double sum, const Polygon& polygon);
  double calculatePolygonAreaRec(const Polygon& polygon, size_t i = 0);
  double calculatePolygonArea(const Polygon& polygon);
}

#endif
