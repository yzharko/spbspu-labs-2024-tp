#ifndef COMMANDS_H
#define COMMANDS_H
#include "Polygon.hpp"
#include <functional>
#include <sstream>
#include <string>

namespace proselkov
{
  double getArea (const Polygon& shape);
  double areaHelper(const Point& point1, const Point& point2);
  double addArea (double area, const Polygon & shape,
      std::function< bool(const Polygon&) > exp);
  double addEveryArea (double area, const Polygon & shape);
  bool hasOddPoints(const Polygon& shape);
  bool hasEvenPoints(const Polygon& shape);
  bool hasNumOfPoints(const Polygon& shape, size_t size);
  bool comparedArea(const Polygon & shape1, const Polygon & shape2);
  bool isRect(const Polygon & shape);
  size_t comparedVert(const Polygon & shape1, const Polygon & shape2);
  std::ostream & area(std::ostream& out,
      std::vector< Polygon > & shapes);
  std::ostream & max(std::ostream& out,
       std::vector< Polygon > & shapes);
  std::ostream & min(std::ostream& out,
       std::vector< Polygon > & shapes);
  std::ostream & count(std::ostream& out,
       std::vector< Polygon > & shapes);
  std::ostream & rects(std::ostream& out,
        std::vector< Polygon > & shapes);
  std::ostream & rmecho(std::ostream& out,
       std::vector< Polygon > & shapes);
}
#endif
