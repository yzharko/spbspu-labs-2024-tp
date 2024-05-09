#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygons.hpp"

namespace kovshikov
{
  int getCordMethod(const Point& currentPoint,const Point& prevPoint);
  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  double countArea(const Polygon polygon);
 // void getOdd(std::ostream& out);
 // void getMean(std::ostream& out);
  void getVertex(std::ostream& out);
 }

#endif
