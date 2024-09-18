#ifndef COMANDS_HPP
#define COMANDS_HPP

#include "polygonFunctions.hpp"

namespace ponomarev
{
  std::ostream & chooseAreaCommand(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & getMax(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & getMin(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & count(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);

  double sumAreasEven(const std::vector< Polygon > & data);
  double sumAreasOdd(const std::vector< Polygon > & data);
  double sumAreasMean(const std::vector< Polygon > & data);
  double sumAreasVertexes(const std::vector< Polygon > & data, int numOfVertexes);

  double getMaxArea(const std::vector< Polygon > & data);
  double getMaxVertexes(const std::vector< Polygon > & data);

  double getMinArea(const std::vector< Polygon > & data);
  double getMinVertexes(const std::vector< Polygon > & data);

  int countEven(const std::vector< Polygon > & data);
  int countOdd(const std::vector< Polygon > & data);
  int countCertain(const std::vector< Polygon > & data, int numOfVertexes);

  std::ostream & countRects(std::istream &, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & countIntersections(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);

  std::ostream & printInvalidCommandMessage(std::ostream & out);
}

#endif
