#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "polygon.hpp"
#include <string>

namespace hohlova
{
  bool isValidFormat(const std::string& line, Polygon& polygon);

  double calcArea(const Polygon& polygon);
  int countVertices(const Polygon& polygon);
  int countPerms(const Polygon& target, const std::vector<Polygon>& polygons);

  std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
  bool comparePoints(const Point& a, const Point& b);
  std::string polygonToString(const Polygon& polygon);

  void processCommands(const std::vector<Polygon>& polygons);

  int countMaxSeq(const Polygon& target, const std::vector<Polygon>& polygons);
  int countRightShapes(const std::vector<Polygon>& polygons);
}

#endif
