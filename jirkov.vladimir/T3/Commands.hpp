#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "geoStructures.hpp"

namespace jirkov
{
  double getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  double getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out);
  double getAreaMean(const std::vector< Polygon >& allData, std::ostream& out);
  void getVertex(std::ostream& out);
  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  int findCordinate(const Point& currentPoint,const Point& prevPoint);
  double countArea(const Polygon polygon);
  double fullArea(double sum, const Polygon polygon);
  bool findEven(const Polygon& polygon);
  bool findOdd(const Polygon& polygon);

 }

#endif
