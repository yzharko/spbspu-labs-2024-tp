#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Point.hpp"

namespace sadofeva
{
  using pr = std::pair< Point, Point >;
  double getAreaAll(const Polygon& polygon);
  bool CompatiblePolygons(Polygon& a, Polygon& b);

  void commandArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out);
  void getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaOdd(const std::vector< Polygon >& polygons,std::ostream& out);
  void getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out);
  void getAreaNum(const std::vector< Polygon >& polygons, std::ostream& out, size_t count);

  void commandMax(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out);
  void getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMaxVertex(const std::vector< Polygon >& polygons, std::ostream& out);

  void commandMin(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out);
  void getMinArea(const std::vector< Polygon >& polygons, std::ostream& out);
  void getMinVertex(const std::vector< Polygon >& polygons, std::ostream& out);

  void commandCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& out);
  void CountEven(const std::vector< Polygon >& polygons, std::ostream& output);
  void CountOdd(const std::vector< Polygon >& polygons, std::ostream& output);
  void CountVertex(const std::vector< Polygon >& polygons, std::ostream& output, size_t count);

  void commandSame(std::vector< Polygon >& polygons, std::istream& input, std::ostream& out);

  bool yComparator(const Point& lhs, const Point& rhs);
  bool xComparator(const Point& lhs, const Point& rhs);
  pr extendFrameRect(pr frameRect, const Polygon& polygon);

  bool isPointInrect(const Point& point, const pr& rect);
  void commandFrame(const std::vector< Polygon >&polygons, std::istream& in, std::ostream& out);
}
#endif
