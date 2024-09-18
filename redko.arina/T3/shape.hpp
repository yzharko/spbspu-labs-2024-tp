#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <vector>
#include <istream>

namespace redko
{
  struct Point
  {
    int x, y;
  };

  std::istream & operator>>(std::istream & in, Point & dest);

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream & operator>>(std::istream & in, Polygon & dest);
}

#endif
