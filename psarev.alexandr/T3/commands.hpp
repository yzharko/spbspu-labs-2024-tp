#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include "polygon.hpp"

namespace psarev
{
  void areaOdd(Polygon&, std::istream&, std::ostream& out);
  void areaEven(int&, std::istream&, std::ostream& out);
  void areaMean(int&, std::istream&, std::ostream& out);
  void areaNumOfVerts(int&, std::istream&, std::ostream& out);
}

#endif