#include "mainExtensions.hpp"

#include <algorithm>
#include <fstream>
#include <limits>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "polygon.hpp"

using polygonArr = std::vector< anikanov::Polygon >;
using funcShema = std::function< bool(const anikanov::Polygon &) >;

std::vector< anikanov::Polygon > anikanov::readPolygons(const std::string &filename)
{
  std::vector< Polygon > polygons;
  std::ifstream input(filename);

  if (!input.is_open()) {
    throw std::runtime_error("Unable to open file");
  }

  while (!input.eof()) {
    Polygon polygon;
    input >> polygon;
    if (!input.fail()) {
      polygons.push_back(polygon);
    } else {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return polygons;
}

std::vector< double > anikanov::getAreas(const polygonArr &polygons)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    areas.push_back(polygon.getArea());
  }
  return areas;
}

std::vector< double > anikanov::getAreasIf(const polygonArr &polygons, funcShema func)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    if (func(polygon)) {
      areas.push_back(polygon.getArea());
    }
  }
  return areas;
}

std::vector< size_t > anikanov::getVertexes(const polygonArr &polygons)
{
  std::vector< size_t > vertexes;
  for (const auto &polygon: polygons) {
    vertexes.push_back(polygon.getSize());
  }
  return vertexes;
}

double anikanov::area(const polygonArr &polygons, std::istream &in)
{
  std::string subcmd;
  in >> subcmd;
  std::vector< double > areas;
  if (subcmd == "ODD") {
    areas = getAreasIf(polygons, [](const Polygon &pol) {
      return pol.getSize() % 2 == 1;
    });
  } else if (subcmd == "EVEN") {
    areas = getAreasIf(polygons, [](const Polygon &pol) {
      return pol.getSize() % 2 == 0;
    });
  } else if (subcmd == "MEAN") {
    areas = getAreas(polygons);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    if (polygons.empty()) {
      throw std::runtime_error("Invalid command");
    }
    return sum / static_cast< double >(polygons.size());
  } else {
    size_t count;

    try {
      count = std::stoull(subcmd);
      if (count < 3) {
        throw std::runtime_error("Invalid command");
      }
    } catch (const std::exception &err) {
      throw std::runtime_error("Invalid command");
    }

    areas = getAreasIf(polygons, [&count](const Polygon &pol) {
      return pol.getSize() == count;
    });
  }
  return std::accumulate(areas.begin(), areas.end(), 0.0);
}

void anikanov::max(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "AREA") {
    std::vector< double > areas = getAreas(polygons);
    auto maxIter = std::max_element(areas.begin(), areas.end());
    if (maxIter != areas.end()) {
      auto maxAreaPolygon = *maxIter;
      out << std::fixed << std::setprecision(1) << maxAreaPolygon << '\n';
      return;
    }
  } else if (subcmd == "VERTEXES") {
    std::vector< size_t > count = getVertexes(polygons);
    auto maxIter = std::max_element(count.begin(), count.end());
    if (maxIter != count.end()) {
      auto maxVertexesPolygon = *maxIter;
      out << std::fixed << std::setprecision(1) << maxVertexesPolygon << '\n';
      return;
    }
  }
  throw std::runtime_error("Invalid command");
}

void anikanov::min(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "AREA") {
    std::vector< double > areas = getAreas(polygons);
    auto minIter = std::min_element(areas.begin(), areas.end());
    if (minIter != areas.end()) {
      auto minAreaPolygon = *minIter;
      out << std::fixed << std::setprecision(1) << minAreaPolygon << '\n';
      return;
    }
  } else if (subcmd == "VERTEXES") {
    std::vector< size_t > count = getVertexes(polygons);
    auto minIter = std::min_element(count.begin(), count.end());
    if (minIter != count.end()) {
      auto minVertexesPolygon = *minIter;
      out << std::fixed << std::setprecision(1) << minVertexesPolygon << '\n';
      return;
    }
  }
  throw std::runtime_error("Invalid command");
}

size_t anikanov::count(const std::vector< Polygon > &polygons, std::istream &in)
{
  size_t count;
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "ODD") {
    count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
      return pol.getSize() % 2 == 1;
    });
  } else if (subcmd == "EVEN") {
    count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
      return pol.getSize() % 2 == 0;
    });
  } else {
    size_t specificNumber;

    try {
      specificNumber = std::stoull(subcmd);
      if (specificNumber < 3) {
        throw std::runtime_error("Invalid command");
      }
    } catch (const std::exception &err) {
      throw std::runtime_error("Invalid command");
    }

    count = std::count_if(polygons.begin(), polygons.end(), [&specificNumber](const Polygon &pol) {
      return pol.getSize() == specificNumber;
    });
  }
  return count;
}

bool anikanov::isRightAngle(const anikanov::Point& A, const anikanov::Point& B, const anikanov::Point& C) {
  // Вычисляем длины сторон треугольника
  double AB = A - B;
  double BC = B - C;
  double AC = A - C;

  // Проверяем теорему Пифагора
  return std::abs(AB * AB + BC * BC - AC * AC) < 1e-9;
}


size_t anikanov::rects(const std::vector< Polygon > &polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
    if (pol.getSize() != 4) {
      return false;
    }

    double side1 = pol[0] - pol[1];
    double side2 = pol[1] - pol[2];
    double side3 = pol[2] - pol[3];
    double side4 = pol[3] - pol[0];

    return side1 == side3 && side2 == side4 && isRightAngle(pol[0], pol[1], pol[2]);
  });
}

bool anikanov::hasRightAngle(const anikanov::Polygon& polygon, size_t index) {
  // Базовый случай: если мы проверили все углы, возвращаем false
  if (index == polygon.getSize()) {
    return false;
  }

  // Проверяем, является ли текущий угол прямым
  if (isRightAngle(polygon[index], polygon[(index+1)%polygon.getSize()], polygon[(index+2)%polygon.getSize()])) {
    return true;
  }

  // Рекурсивный вызов для следующего угла
  return anikanov::hasRightAngle(polygon, index + 1);
}

size_t anikanov::rightShapes(const std::vector< Polygon > &polygons)
{
  return  std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol){
    return anikanov::hasRightAngle(pol);
  });
}
