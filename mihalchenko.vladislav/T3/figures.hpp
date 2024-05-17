#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>

namespace mihalchenko
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  std::istream &operator>>(std::istream &is, Point &rhs);
  std::ostream &operator<<(std::ostream &out, const Point &rhs);
  std::istream &operator>>(std::istream &is, Polygon &rhs);
  std::ostream &operator<<(std::ostream &out, const Polygon &rhs);
}

#endif
