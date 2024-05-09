#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <functional>
#include <algorithm>
#include "dataStruct.hpp"

namespace nikiforov
{
  void takingArea(const std::vector< Polygon >& shapes, std::istream&, std::ostream& out);
  int getPoints(const Point& first, const Point& second);
  double getArea(const Polygon& polygon);

  bool isOdd(const Polygon& polygon);
  bool isEven(const Polygon& polygon);
  bool numOfVert(size_t num, const Polygon& polygon);

  void takingMax(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);
  size_t countOfVertexes(const Polygon& polygon);

  void takingMin(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);

  void takingCount(const std::vector< Polygon >& shapes, std::istream& in, std::ostream& out);

  double getAreaResult(const std::vector< Polygon >& shapes, std::string mode);
  size_t getVertexesResult(const std::vector< Polygon >& shapes, std::string mode);

  void takingIntersections(const std::vector< Polygon >& shapes, std::istream& input, std::ostream& out);
  std::pair< Point, Point > getPointsInter(const Point& first, const Point& second);
  size_t intersectingLines(const std::vector< std::pair< Point, Point > >& vectorsIntersectios, const Polygon& shapes);
  bool intersectingShapes(const std::pair < Point, Point >& vectIntersectios, const Polygon& polygon);
  bool intersecting(const std::pair < Point, Point >& vectPolygon, const std::pair < Point, Point >& vectIntersectios);
  bool doIntersect(Point p1, Point q1, Point p2, Point q2);
  int orientation(Point p, Point q, Point r);
  bool onSegment(Point p, Point q, Point r);

  void takingSame(const std::vector< Polygon >& shapes, std::istream& input, std::ostream& out);
  bool countSame(const Polygon& polygonSame, const Polygon& polygonShape);
  int pointsSame(const Point& first, const Point& second);

  void takingError(std::ostream& out, const std::string& errorStr);

}

#endif
