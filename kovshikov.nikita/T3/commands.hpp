#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygons.hpp"

namespace kovshikov
{
  //void getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out);
  void getArea(std::istream&, std::ostream& out);
  void getEven(std::ostream& out);
  void getOdd(std::ostream& out);
  void getMean(std::ostream& out);
  void getVertex(std::ostream& out);
 }

#endif
