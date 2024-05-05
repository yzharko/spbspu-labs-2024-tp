#ifndef COMANDS_HPP
#define COMANDS_HPP
#include "shape.hpp"

namespace redko
{
  std::ostream & countAreas(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes);
  double countAreasEven(const std::vector< Polygon > & shapes);
  double countAreasOdd(const std::vector< Polygon > & shapes);
  double countAreasMean(const std::vector< Polygon > & shapes);
  double countAreasVertexes(const std::vector< Polygon > & shapes, int numOfVertexes);

  std::ostream & getMax(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes);
  double getMaxArea(const std::vector< Polygon > & shapes);
  double getMaxVertexes(const std::vector< Polygon > & shapes);

  std::ostream & getMin(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes);
  double getMinArea(const std::vector< Polygon > & shapes);
  double getMinVertexes(const std::vector< Polygon > & shapes);

  std::ostream & count(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes);
  int countEven(const std::vector< Polygon > & shapes);
  int countOdd(const std::vector< Polygon > & shapes);
  int countShapes(const std::vector< Polygon > & shapes, int numOfVertexes);

  std::ostream & countIntersections(std::istream & in, std::ostream & out, const std::vector< Polygon > & shapes);
  std::ostream & countRightShapes(std::istream &, std::ostream & out, const std::vector< Polygon > & shapes);

  std::ostream & printMessage(std::ostream & out, const std::string & message);
}

#endif
