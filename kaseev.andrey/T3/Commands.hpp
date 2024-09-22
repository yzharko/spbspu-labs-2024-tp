#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Polygon.hpp"
#include <functional>

namespace kaseev
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
  size_t comparedVert(const Polygon & shape1, const Polygon & shape2);
  std::ostream & area(std::istream& in, std::ostream& out,
                      std::vector< Polygon > & shapes);
  std::ostream & max(std::istream& in, std::ostream& out,
                     std::vector< Polygon > & shapes);
  std::ostream & min(std::istream& in, std::ostream& out,
                     std::vector< Polygon > & shapes);
  std::ostream & count(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes);
  std::ostream & perms(std::istream& in, std::ostream& out,
                       std::vector< Polygon > & shapes);
  std::ostream &echoCommand(std::istream &in, std::ostream &out,
                            std::vector< Polygon > & shapes);
}
#endif
