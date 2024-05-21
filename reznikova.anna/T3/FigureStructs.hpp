#ifndef FIGURESTRUCTS_HPP
#define FIGURESTRUCTS_HPP
#include <vector>
#include <iostream>

namespace reznikova
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & is, Point & value);

  struct Polygon
  {
    std::vector< Point > points;
  };
  std::istream & operator>>(std::istream & is, Polygon & value);
}
#endif

