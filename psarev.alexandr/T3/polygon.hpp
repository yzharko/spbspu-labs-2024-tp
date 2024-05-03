#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>

namespace psarev
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct intIO
  {
    int& ref;
  };

  std::istream& operator>>(std::istream& in, intIO&& dest);

  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream& operator>>(std::istream& in, Polygon& figure);
}

#endif
