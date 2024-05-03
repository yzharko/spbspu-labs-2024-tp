#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include "polygon.hpp"
#include "checkFuncs.hpp"

namespace psarev
{
  std::ostream& chooseAreaType(std::vector< Polygon >& polyVec, std::istream&, std::ostream& out);
  void getEvenArea(std::vector< Polygon >& polyVec, std::ostream& out);

  //double getOddArea(std::vector< Polygon >& polyVec);
  //double getMeanArea(std::vector< Polygon >& polyVec);
  //double getNoVArea(std::vector< Polygon >& polyVec, int verts);
}

#endif