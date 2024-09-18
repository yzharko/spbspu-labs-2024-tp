#include "rects.hpp"
#include "polygon.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

int main() {
  FigureCollection collection;
  std::vector<Polygon> polygons;
  std::string line;
  int removedCount = 0;

  std::ifstream figureFile("figures.txt");
  while (std::getline(figureFile, line)) {
  std::istringstream iss(line);
  int vertexCount;
  if (!(iss >> vertexCount)) continue;

  std::vector<std::pair<double, double>> vertices;
  double x, y;
  for (int i = 0; i < vertexCount; ++i) {
      if (!(iss >> x >> y)) break;
      vertices.emplace_back(x, y);
  }

  if (vertices.size() == vertexCount) {
        collection.addFigure(Figure(vertices));
  }
}

  std::ifstream polygonFile("polygons.txt");
  while (std::getline(polygonFile, line)) {
  std::istringstream iss(line);
  int vertices;
  std::vector<std::pair<int, int>> points;
  if (iss >> vertices) {
      points.resize(vertices);
     for (int i = 0; i < vertices; ++i) {
        iss >> points[i].first >> points[i].second;
     }
        polygons.emplace_back(vertices, points);
  }
}

 polygons = removeDuplicates(polygons, removedCount);
 std::cout << "Removed figures: " << removedCount << std::endl;

  for (const auto& polygon : polygons) {
      std::cout << polygon.getVerticesCount() << " ";
      for (const auto& point : polygon.points) {
      std::cout << "(" << point.first << ";" << point.second << ") ";
  }
  std::cout << std::endl;
}

  std::cout << "AREA ODD: " << collection.calculateArea("ODD") << std::endl;
  std::cout << "AREA EVEN: " << collection.calculateArea("EVEN") << std::endl;
  std::cout << "AREA MEAN: " << collection.calculateMeanArea() << std::endl;
  std::cout << "MAX AREA: " << collection.maxArea() << std::endl;
  std::cout << "MIN AREA: " << collection.minArea() << std::endl;
  std::cout << "COUNT ODD: " << collection.countFigures("ODD") << std::endl;
  std::cout << "COUNT EVEN: " << collection.countFigures("EVEN") << std::endl;

  processCommands(polygons);

  return 0;
}
