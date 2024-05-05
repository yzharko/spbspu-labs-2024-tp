#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
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
  size_t countIf(size_t result, const Polygon & polygon, size_t mode, bool inpMode);
  long long areaTriangl(Point a, Point b, Point c);
  bool intersect_1(int a, int b, int c, int d);
  bool intersectVectorPointOnLine(Point a, Point b, Point c);
  bool intersectVectors(Point a, Point b, Point c, Point d);
  bool intersectPolygAndVect(const Polygon & polygon, Point a, Point b);
  bool intersectPolyg(const Polygon & polygon1, const Polygon & polygon2);
  bool isSamePolyg(const Polygon & polyg1, const Polygon & polyg2);
  bool isEqual(const Polygon & polyg1, const Polygon & polyg2);
}

#endif
