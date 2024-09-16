#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "geoStructures.hpp"

namespace jirkov
{
  void getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out);
  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  int findCordinate(const Point& currentPoint,const Point& prevPoint);
  double countArea(const Polygon polygon);
  double fullArea(double sum, const Polygon polygon);
  bool findEven(const Polygon& polygon);
  bool findOdd(const Polygon& polygon);
  bool findVertex(unsigned long long num, Polygon polygon);
}

#endif
