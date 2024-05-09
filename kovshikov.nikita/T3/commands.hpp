#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygons.hpp"

namespace kovshikov
{
  int getCordMethod(const Point& currentPoint,const Point& prevPoint);
  double countArea(const Polygon polygon);

  double resultArea(double summa, const Polygon polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);

  double getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  double getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out);
  double getAreaMean(const std::vector< Polygon >& allData, std::ostream& out);

  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getVertex(std::ostream& out);
}

#endif
