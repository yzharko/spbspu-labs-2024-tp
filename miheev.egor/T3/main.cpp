#include <iostream>
#include <sstream>
#include "geometry.hpp"

int main()
{
  using namespace miheev;
  std::stringstream in("3 (0;0) (0;2) (1;0)");
  Polygon p;
  in >> p;
  std::cout << getArea(p) << '\n';
  return 0;
}

