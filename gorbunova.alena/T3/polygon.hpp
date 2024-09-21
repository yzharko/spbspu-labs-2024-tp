#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "delimiter.hpp"
#include "iofmtguard.hpp"

namespace gorbunova
{
  struct Point
  {
    int x, y;
    bool operator==(const Point &other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    bool operator==(const Polygon &other) const;
    double calculateArea() const;
  };
  std::ostream &operator<<(std::ostream &os, const Point &point);
  std::istream &operator>>(std::istream &is, Point &point);
  std::ostream &operator<<(std::ostream &os, const Polygon &polygon);
  std::istream &operator>>(std::istream &is, Polygon &polygon);
  std::vector< Polygon > readPolygonsFromFile(const std::string &filename);
  void processCommand(const std::string &command, std::vector< Polygon > &polygons);
  double calculateAreaSum(const std::vector< Polygon > &polygons, std::function< bool(const Polygon &) > filter);
  size_t countPolygons(const std::vector< Polygon > &polygons, std::function< bool(const Polygon &) > filter);
  Polygon parsePolygonFromCommand(std::istream &is);
}

#endif
