#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "FigureStructs.hpp"

namespace reznikova
{
  double getArea(const Polygon & polygon);
  size_t getNumOfVertexes(const Polygon & polygon);
  std::vector< Polygon > chooseOddPolygons(const std::vector< Polygon > & polygons);
  std::vector< Polygon > chooseEvenPolygons(const std::vector< Polygon > & polygons);
  bool checkIfSame(size_t num, const Polygon & polygon);
  std::vector< Polygon > chooseNumPolygons(const std::vector< Polygon > & polygons, size_t num);
  std::vector< double > getAllAreas(const std::vector< Polygon > & polygons);
  std::vector< size_t > getAllVertexes(const std::vector< Polygon > & polygons);
  double getSumArea(const std::vector< Polygon > & polygons);
  void areaCommand(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is);
  void maxCommand(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is);
  void minCommand(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is);
  void countCommand(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is);
  bool checkIfPointsEqual(const Point & first_point, const Polygon & polygon);
  bool checkIfPerms(const Polygon & base_polygon, const Polygon & polygon);
  void permsCommand(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is);
  bool checkIfParallelogram(const Polygon & polygon);
  bool checkIfRect(const Polygon & polygon);
  void rectsCommand(const std::vector< Polygon > & polygons, std::ostream & out);
  void getOutputMessage(std::ostream & out);
}

#endif
