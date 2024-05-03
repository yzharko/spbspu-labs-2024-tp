#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include "polygon.hpp"
#include "internalFuncs.hpp"

namespace psarev
{
  std::ostream& chooseAreaType(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);
  std::ostream& chooseMaxOpt(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);
  std::ostream& chooseMinOpt(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);
  std::ostream& chooseCountOpt(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);
  std::ostream& countRects(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);

  void getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out);
  void getOddArea(std::vector< Polygon >& polyVec, std::ostream& out);
  void getMeanArea(std::vector< Polygon >& polyVec, std::ostream& out);
  void getAreaNumVerts(std::vector< Polygon >& polyVec, std::ostream& out, size_t& numVerts);

  void getMaxArea(std::vector< Polygon >& polyVec, std::ostream& out);
  void getMinArea(std::vector< Polygon >& polyVec, std::ostream& out);
  void getMaxVerts(std::vector< Polygon >& polyVec, std::ostream& out);
  void getMinVerts(std::vector< Polygon >& polyVec, std::ostream& out);

  void countEvenVerts(std::vector< Polygon >& polyVec, std::ostream& out);
  void countOddVerts(std::vector< Polygon >& polyVec, std::ostream& out);
  void countSpecVerts(std::vector< Polygon >& polyVec, std::ostream& out, size_t& numVerts);
}

#endif
