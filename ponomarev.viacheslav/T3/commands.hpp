#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <vector>
#include <ostream>
#include <map>
#include "polygon.hpp"

namespace ponomarev
{
  std::ostream & chooseAreaCommand(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & getMax(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & getMin(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);
  std::ostream & count(std::istream & in, std::ostream & out, const std::vector< Polygon > & data);

  double sumAreasEven(const std::vector< Polygon > & data);
  double sumAreasOdd(const std::vector< Polygon > & data);
  double countAreasMean(const std::vector< Polygon > & data);
  double countSumAreasVertexes(const std::vector< Polygon > & data, int numOfVertexes);

  double getMaxArea(const std::vector< Polygon > & data);
  double getMaxVertexes(const std::vector< Polygon > & data);

  double getMinArea(const std::vector< Polygon > & data);
  double getMinVertexes(const std::vector< Polygon > & data);

  int countEven(const std::vector< Polygon > & data);
  int countOdd(const std::vector< Polygon > & data);
  int countdata(const std::vector< Polygon > & data, int numOfVertexes);

  std::ostream & printMessage(std::ostream & out, const std::string & message);
}

#endif
