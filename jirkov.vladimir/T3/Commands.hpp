#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "geoStructures.hpp"

namespace jirkov
{
  void getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getOdd(std::ostream& out);
  void getMean(std::ostream& out);
  void getVertex(std::ostream& out);

  int findCordinate(const Point& currentPoint,const Point& prevPoint);
  double countArea(const Polygon polygon);
 }

#endif
