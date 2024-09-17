#include "rects.hpp"
#include <stdexcept>

Figure::Figure(const std::vector<std::pair<double, double>>& vertices) : vertices_(vertices) {}

double Figure::area() const {
  double area = 0.0;
  int n = vertices_.size();
  for (int i = 0; i < n; ++i) {
      area += (vertices_[i].first * vertices_[(i + 1) % n].second) - (vertices_[(i + 1) % n].first * vertices_[i].second);
  }
  return std::abs(area) / 2.0;
}

int Figure::vertexCount() const {
  return vertices_.size();
}

void FigureCollection::addFigure(const Figure& figure) {
  figures_.push_back(figure);
}

double FigureCollection::calculateArea(const std::string& type) const {
  double totalArea = 0.0;
  for (const auto& figure : figures_) {
      if ((type == "EVEN" && figure.vertexCount() % 2 == 0) ||
        (type == "ODD" && figure.vertexCount() % 2 != 0)) {
        totalArea += figure.area();
      }
  }
  return totalArea;
}

double FigureCollection::calculateMeanArea() const {
  if (figures_.empty()) throw std::runtime_error("No figures available.");
  double totalArea = 0.0;
  for (const auto& figure : figures_) {
     totalArea += figure.area();
  }
  return totalArea / figures_.size();
}

int FigureCollection::countFigures(const std::string& type) const {
  int count = 0;
  for (const auto& figure : figures_) {
      if ((type == "EVEN" && figure.vertexCount() % 2 == 0) ||
          (type == "ODD" && figure.vertexCount() % 2 != 0) ||
          (type == std::to_string(figure.vertexCount()))) {
          count++;
      }
  }
  return count;
}

double FigureCollection::maxArea() const {
  if (figures_.empty()) throw std::runtime_error("No figures available.");
  double maxArea = figures_[0].area();
  for (const auto& figure : figures_) {
      maxArea = std::max(maxArea, figure.area());
  }
  return maxArea;
}

double FigureCollection::minArea() const {
  if (figures_.empty()) throw std::runtime_error("No figures available.");
  double minArea = figures_[0].area();
  for (const auto& figure : figures_) {
    minArea = std::min(minArea, figure.area());
  }
  return minArea;
}

int FigureCollection::maxVertexCount() const {
  if (figures_.empty()) throw std::runtime_error("No figures available.");
  int maxCount = figures_[0].vertexCount();
  for (const auto& figure : figures_) {
      maxCount = std::max(maxCount, figure.vertexCount());
  }
  return maxCount;
}

int FigureCollection::minVertexCount() const {
  if (figures_.empty()) throw std::runtime_error("No figures available.");
  int minCount = figures_[0].vertexCount();
  for (const auto& figure : figures_) {
    minCount = std::min(minCount, figure.vertexCount());
  }
  return minCount;
}
