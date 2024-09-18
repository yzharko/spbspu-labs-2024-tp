#include "polygon.hpp"
#include <cmath>

Polygon::Polygon(int vertices, const std::vector<std::pair<int, int>>& points)
   : verticesCount(vertices), points(points) {}

double Polygon::area() const {
  double area = 0.0;
  for (size_t i = 0; i < points.size(); ++i) {
      int j = (i + 1) % points.size();
      area += points[i].first * points[j].second;
      area -= points[j].first * points[i].second;
  }
  return std::abs(area) / 2.0;
}

int Polygon::getVerticesCount() const {
  return verticesCount;
}

bool Polygon::operator<(const Polygon& other) const {
  return points < other.points;
}

std::vector<Polygon> removeDuplicates(const std::vector<Polygon>& polygons, int& removedCount) {
  std::set<Polygon> uniquePolygons(polygons.begin(), polygons.end());
  removedCount = polygons.size() - uniquePolygons.size();
  return std::vector<Polygon>(uniquePolygons.begin(), uniquePolygons.end());
}

void processCommands(const std::vector<Polygon>& polygons){

}
