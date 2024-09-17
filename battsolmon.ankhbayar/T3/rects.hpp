#ifndef RECTS_HPP
#define RECTS_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>

class Figure {
public:
  Figure(const std::vector<std::pair<double, double>>& vertices);
  double area() const;
  int vertexCount() const;

private:
  std::vector<std::pair<double, double>> vertices_;
};

class FigureCollection {
public:
  void addFigure(const Figure& figure);
  double calculateArea(const std::string& type) const;
  double calculateMeanArea() const;
  int countFigures(const std::string& type) const;
  double maxArea() const;
  double minArea() const;
  int maxVertexCount() const;
  int minVertexCount() const;

private:
  std::vector<Figure> figures_;
};

#endif // PRIM_HPP
