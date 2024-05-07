#ifndef FIGURES_HPP
#define FIGURES_HPP

// #include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
// #include <string>
// #include <utility>
// #include <algorithm>

// #include <functional>
#include <numeric>

namespace mihalchenko
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector<Point> points;
  };

  struct DelimiterIO
  {
    char expected;
  };

  struct ComplexIO
  {
    std::pair<double, double> &ref;
  };

  std::istream &operator>>(std::istream &is, DelimiterIO &&exp);
  std::istream &operator>>(std::istream &is, Point &rhs);
  std::ostream &operator<<(std::ostream &out, const Point &rhs);
  std::istream &operator>>(std::istream &is, Polygon &rhs);
  std::ostream &operator<<(std::ostream &out, const Polygon &rhs);
}

#endif
