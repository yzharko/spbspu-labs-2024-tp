#include "rects.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

int main() {
  FigureCollection collection;
  std::ifstream file("figures.txt");
  std::string line;

  while (std::getline(file, line)) {
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

  std::cout << "AREA ODD: " << collection.calculateArea("ODD") << std::endl;
  std::cout << "AREA EVEN: " << collection.calculateArea("EVEN") << std::endl;
  std::cout << "AREA MEAN: " << collection.calculateMeanArea() << std::endl;
  std::cout << "MAX AREA: " << collection.maxArea() << std::endl;
  std::cout << "MIN AREA: " << collection.minArea() << std::endl;
  std::cout << "COUNT ODD: " << collection.countFigures("ODD") << std::endl;
  std::cout << "COUNT EVEN: " << collection.countFigures("EVEN") << std::endl;

  return 0;
}
