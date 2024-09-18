#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <string>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>

class Polygon {
public:
  Polygon(int vertices, const std::vector<std::pair<int, int>>& points);
  double area() const;
  int getVerticesCount() const;
  bool operator<(const Polygon& other) const;

private:
  int verticesCount;
  std::vector<std::pair<int, int>> points;
};

std::vector<Polygon> removeDuplicates(const std::vector<Polygon>& polygons, int& removedCount);
void processCommands(const std::vector<Polygon>& polygons);

#endif // POLYGON_HPP
