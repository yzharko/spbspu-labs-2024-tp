#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <iomanip>
#include <cctype>
#include <vector>

namespace lisitsyna
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  bool comparatorArea(Polygon fst, Polygon snd);

  bool comparatorVertexes(Polygon fst, Polygon snd);

  bool operator==(Point& src1, Point& src2);

  bool operator==(Polygon& src1, Polygon& src2);

  bool operator!=(Polygon& src1, Polygon& src2);

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Point& dest);

  double getArea(const Polygon& data);

  bool isParallelogram(const Polygon& data);

  bool isRect(const Polygon& data);
}
#endif
