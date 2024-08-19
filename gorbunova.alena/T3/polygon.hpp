#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include <string>

struct Point
{
  int x, y;
  bool operator==(const Point &other) const;
};

struct Polygon
{
  std::vector<Point> points;
  bool operator==(const Polygon &other) const;
  double calculateArea() const;
};

std::vector<Polygon> readPolygonsFromFile(const std::string &filename);
void processCommand(const std::string &command, std::vector<Polygon> &polygons);

#endif
