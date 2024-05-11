#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygons.hpp"

namespace kovshikov
{
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

  void getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out);

  void getMaxArea(const std::vector< Polygon >& allData, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& allData, std::ostream& out);

  void getMinArea(const std::vector< Polygon >& allData, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& allData, std::ostream& out);

  void countEven(const std::vector< Polygon >& allData, std::ostream& out);
  void countOdd(const std::vector< Polygon >& allData, std::ostream& out);
  void countVertexes(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out);

  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getMax(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getMin(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void count(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void countRightshapes(const std::vector< Polygon >& allData, std::ostream& out);
  void checkInframe(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);

  int getX(const Point& point);
  int getY(const Point& point);

  int getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
  int getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point));
  std::vector< Point > getFrame(const std::vector< Polygon >& allData);
  bool isInframe(const std::vector< Polygon >& allData, const Polygon& polygon);
}

#endif
