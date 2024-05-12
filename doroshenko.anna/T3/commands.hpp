#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include "polygon.hpp"

namespace doroshenko
{
  void cmdArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void evenArea(const std::vector< Polygon >& polygons, std::ostream& output);
  void oddArea(const std::vector< Polygon >& polygons, std::ostream& output);
  void meanArea(const std::vector< Polygon >& polygons, std::ostream& output);
  void vertexArea(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
  double plusArea(double sum, const Polygon& polygon);
  double calculatePolygonArea(const Polygon& polygon);
  double calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area);

  void cmdMax(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void findMaxArea(const std::vector< Polygon >& polygons, std::ostream& output);
  void findMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& output);

  void cmdMin(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void findMinArea(const std::vector< Polygon >& polygons, std::ostream& output);
  void findMinVertexes(const std::vector< Polygon >& polygons, std::ostream& output);


  void cmdCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output);
  void countEven(const std::vector< Polygon >& polygons, std::ostream& output);
  void countOdd(const std::vector< Polygon >& polygons, std::ostream& output);
  void vertexCount(size_t num, const std::vector< Polygon >& polygons, std::ostream& output);
}

#endif
