#ifndef COMAND_HPP
#define COMAND_HPP

#include <vector>
#include "Polygon.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  size_t countVertexes(const Polygon& polygon);
  double getAreas(const Point& pointOne, const Point& pointTwo);
  double getArea(const Polygon& polygon);
  void AreaEven(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaEven(double area, const Polygon& polygon);
  void AreaOdd(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaOdd(double area, const Polygon& polygon);
  void AreaMean(const std::vector< Polygon >& polygon, std::ostream& out);
  double getAreaSum(double area, const Polygon& polygon);
  void AreaNum(const std::vector< Polygon >& polygon, std::ostream& out, size_t type);
  double getAreaNum(double area, const Polygon& polygon, size_t vertexes);

  void MaxComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  void MaxArea(const std::vector< Polygon >& polygon, std::ostream& out);
  void MaxVertexes(const std::vector< Polygon >& polygon, std::ostream& out);

  void MinComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  void minArea(const std::vector< Polygon >& polygon, std::ostream& out);
  void minVertexes(const std::vector< Polygon >& polygon, std::ostream& out);

  void CountComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out);
  bool EvenVertexes(const Polygon& polygon);
  bool OddVertexes(const Polygon& polygon);
  void EvenCount(const std::vector< Polygon >& polygon, std::ostream& out);
  void OddCount(const std::vector< Polygon >& polygon, std::ostream& out);
  bool Vertexes(const Polygon& polygon, size_t type);
  void VertexesCount(const std::vector< Polygon >& polygon, std::ostream& out, size_t type);
}
#endif
