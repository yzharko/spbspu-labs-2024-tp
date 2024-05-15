#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <cstring>
#include "for_commands.hpp"
#include "polygons.hpp"

namespace kovshikov
{
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
}

#endif
