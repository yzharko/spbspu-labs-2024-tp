#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace sobolevsky
{
  void area(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void getMax(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void getMin(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void count(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void intersections(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);
  void same(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out);

  double areaIf(double result, const sobolevsky::Polygon & polygon, size_t mode, bool inpMode);
  bool getMaxMinArea(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2);
  bool getMaxMinVertex(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2);
  size_t countIf(size_t result, const sobolevsky::Polygon & polygon, size_t mode, bool inpMode);
  size_t areaTriangl(sobolevsky::Point a, sobolevsky::Point b, sobolevsky::Point c);
  bool intersect_1(size_t a, size_t b, size_t c, size_t d);
  bool intersectVectors(sobolevsky::Point a, sobolevsky::Point b, sobolevsky::Point c, sobolevsky::Point d);
  bool intersectPolygAndVect(const sobolevsky::Polygon & polygon, sobolevsky::Point a, sobolevsky::Point b);
  bool intersectPolyg(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2);
}

#endif
