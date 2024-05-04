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

  int diffMultPair(const Point & firstP, const Point & secondP);
  Point makeVector(const Point & firstP, const Point & secondP);
  int makeScalar(const Point & firstV, const Point & secondV);
  int makeVectorMultiply(const Point & point, const Point & firstP, const Point & secondP);

  std::istream & operator>>(std::istream & in, Point & dest);

  struct Polygon
  {
    std::vector< Point > points;
  };

  double countArea(const Polygon & shape);
  double sumAreas(double res, const Polygon & shape);
  double sumAreasIfEven(double res, const Polygon & shape);
  double sumAreasIfOdd(double res, const Polygon & shape);
  double sumAreasIfEqual(double res, const Polygon & shape, size_t numOfVertexes);
  int getNumOfVertexes(const Polygon & shape);
  bool isNumOfVertexesEven(const Polygon shape);
  bool isNumOfVertexesOdd(const Polygon shape);
  bool isNumOfVertexesEqual(const Polygon shape, size_t numOfVertexes);
  bool isPointInPolygon(const Point & point, const Polygon & shape);
  bool isIntersected(const Polygon & firstS, const Polygon & secondS);
  bool isEqual(int firstN, int secondN);
  bool isRightShape(const Polygon & shape);

  std::istream & operator>>(std::istream & in, Polygon & dest);
}

#endif
