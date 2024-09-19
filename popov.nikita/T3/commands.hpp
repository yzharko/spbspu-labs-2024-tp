#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "polygon.hpp"

namespace popov
{
  std::ostream & getArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  double getAreaEven(const std::vector< Polygon > & polygons);
  bool isPolygonEven(const Polygon& polygon);
  double getAreaOdd(const std::vector< Polygon > & polygons);
  bool isPolygonOdd(const Polygon& polygon);
  double getAreaMean(const std::vector< Polygon > & polygons);
  double getAreaVertexes(const std::vector< Polygon > & polygons, int num);
  std::vector< double > getAreas(const std::vector< Polygon > & polygons);
  double calculateAreaAndPushBack(const Polygon& polygon);
  double getsArea(const Polygon & polygon);
  double calculateArea(const Point& p1, const Point& p2);
  double accumulateArea(double sum, const Point& p, const std::vector<Point>& polygon);
  bool hasNumVertexes(const Polygon& polygon, int num);
  std::ostream& maxCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  std::vector< double > maxArea(const std::vector< Polygon >& polygons);
  double calculatingArea(const Polygon& polygon);
  std::vector< int > maxVertexes(const std::vector< Polygon >& polygons);
  int numOfVertexes(const Polygon & polygon);
  std::ostream& minCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  std::ostream& count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  int evenCount(const std::vector< Polygon >& polygons);
  int oddCount(const std::vector< Polygon >& polygons);
  int vertCount(const std::vector< Polygon >& polygons, int n);
  std::ostream& inframe(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  std::pair<Point, Point> findMinMaxXY(const std::vector< Polygon >& polygons);
  int minPolygonX(const Polygon& polygon);
  int minPolygonY(const Polygon& polygon);
  int maxPolygonX(const Polygon& polygon);
  int maxPolygonY(const Polygon& polygon);
  bool compareX(const Point& p1, const Point& p2);
  bool compareY(const Point& p1, const Point& p2);
  int getMinX(const Polygon& polygon);
  int getMinY(const Polygon& polygon);
  int getMaxX(const Polygon& polygon);
  int getMaxY(const Polygon& polygon);
  std::ostream& maxSeq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  int countSeq(const popov::Polygon& polygon, const popov::Polygon& polyg, int& counter);
  bool operator==(const Polygon& p1, const Polygon& p2);
  bool operator==(const Point& p1, const Point& p2);

  void invalidMessage(std::ostream& out);
}

#endif
