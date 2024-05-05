#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "polygon.hpp"

namespace sobolevsky
{
  void area(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);
  void getMax(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);
  void getMin(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);
  void count(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);
  void intersections(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);
  void same(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out);

  double areaIf(double result, const Polygon & polygon, size_t mode, bool inpMode);
  bool getMaxMinArea(const Polygon & polygon1, const Polygon & polygon2);
  bool getMaxMinVertex(const Polygon & polygon1, const Polygon & polygon2);
  bool countIf(const Polygon & polygon, size_t mode, bool inpMode);
  long long areaTriangl(Point a, Point b, Point c);
  bool intersect_1(int a, int b, int c, int d);
  bool intersectVectorPointOnLine(Point a, Point b, Point c);
  bool intersectVectors(Point a, Point b, const Polygon & polygon, size_t i);
  bool intersectPolygAndVect(const Polygon & polygon1, const Polygon & polygon2, size_t i);
  bool intersectPolyg(const Polygon & polygon1, const Polygon & polygon2);
  bool findDifference(const Polygon & polyg1, const Polygon & polyg2, int difX, int difY, int i);
  bool isSamePolyg(const Polygon & polyg1, const Polygon & polyg2);
  bool isEqual(const Polygon & polyg1, const Polygon & polyg2);
  void error(std::ostream & out, const std::string & text);
}

#endif
