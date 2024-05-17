#ifndef FORCOMMANDS_HPP
#define FORCOMMANDS_HPP
#include <cstring>
#include "polygons.hpp"

namespace kovshikov
{
  void getCheck(std::string command,
                  void(*getFunction)(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out),
                    const std::vector< Polygon >& allData, std::ostream& out);

  void fileIsEmpty(const std::vector< Polygon >& allData);
  bool isDigit(char ch);
  int getCordMethod(const Point& currentPoint,const Point& prevPoint);
  double countArea(const Polygon polygon);

  double resultArea(double summa, const Polygon polygon);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isThisVertex(unsigned long long num, Polygon polygon);
  unsigned long long getVertexes(const Polygon& polygon);
  Point createVector(const Point& next, const Point& current);
  int getScalar(const Point& next, const Point& current);
  bool isRight(int scalar);
  bool isPolygonRight(const Polygon& polygon);

  int getX(const Point& point);
  int getY(const Point& point);

  int getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
  int getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
  std::vector< Point > getFrame(const std::vector< Polygon >& allData);
  bool isInframe(const std::vector< Polygon >& allData, const Polygon& polygon);
  void outputError(std::ostream& out);
}

#endif
