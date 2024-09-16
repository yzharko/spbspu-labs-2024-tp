#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <ios>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <limits>

namespace proselkov
{
  struct Point
  {
    int x, y;
    bool operator ==(const Point& p1) const
    {
      return ((p1.x == this->x) && (p1.y == this->y));
    }
  };
  struct Polygon
  {
    std::vector< Point > points;
    bool operator ==(const Polygon& p1) const
    {
      if (p1.points.size() != this->points.size())
      {
        return false;
      }
      return (p1.points == this->points);
    }
  };
  struct DelimiterIO
  {
    char exp;
  };
  std::istream& operator >>(std::istream& in, Point& dest);
  std::istream& operator >>(std::istream& in, Polygon& dest);
  std::istream& operator >>(std::istream& in, DelimiterIO&& dest);

  bool operator >(const Point& p1, const Point& p2);

  template < class T >
  T maxOfTwo(T x, T y)
  {
    return (x > y ? x : y);
  }
  template < class T >
  T minOfTwo(T x, T y)
  {
    return (x < y ? x : y);
  }
}
#endif
