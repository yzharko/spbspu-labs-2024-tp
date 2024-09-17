#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygons.hpp"

namespace jirkov
{
  void getAreaEven(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& allData, std::ostream& out);
  void getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out);
  void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& allData, std::ostream& out);
  void getMaxVertexes(const std::vector< Polygon >& allData, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& allData, std::ostream& out);
  void getMinVertexes(const std::vector< Polygon >& allData, std::ostream& out);
  void getMax(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getMin(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void countEven(const std::vector< Polygon >& allData, std::ostream& out);
  void countOdd(const std::vector< Polygon >& allData, std::ostream& out);
  void count(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void checkPerms(const std::vector< Polygon > & allData, std::istream & is, std::ostream & out);
  void countVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out);
  void fileIsEmpty(const std::vector< Polygon >& allData);
  bool findEqual(const Point & firstPoint, const Polygon & allData);
  int findCordinate(const Point& currentPoint,const Point& prevPoint);
  unsigned long long getVertex(const Polygon& polygon);

  double countArea(const Polygon polygon);
  double fullArea(double sum, const Polygon polygon);
  bool findPerms(const Polygon & basePolygon, const Polygon & polygon);
  bool findEven(const Polygon& polygon);
  bool findOdd(const Polygon& polygon);
  bool findVertex(unsigned long long num, Polygon polygon);
  bool isDigit(char ch);
}

#endif
