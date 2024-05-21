#include "mainExtensions.hpp"

#include <algorithm>
#include <fstream>
#include <limits>
#include <guard.hpp>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "polygon.hpp"

using polygonArr = std::vector< anikanov::Polygon >;
using funcShema = std::function< bool(const anikanov::Polygon &) >;

void anikanov::printErrorMessage(std::ostream &out)
{
  iofmtguard guard(std::cout);
  out << std::fixed << std::setprecision(1);

  out << "<INVALID COMMAND>\n";
}

double anikanov::getLenght(const Point &p1, const Point &p2)
{
  return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

double anikanov::getArea(const Polygon &polygon)
{
  auto points_cycled = polygon.points;
  points_cycled.push_back(polygon.points[0]);

  std::vector< double > areas;
  areas.resize(points_cycled.size() - 1);
  std::transform(points_cycled.begin(), --points_cycled.end(), ++points_cycled.begin(), areas.begin(),
                 [](const Point &point1, const Point &point2) {
                   return areaHelper(point1, point2);
                 });
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  return std::fabs(area / 2.0);
}

double anikanov::areaHelper(const Point &point1, const Point &point2)
{
  return (point1.x * point2.y - point1.y * point2.x);
}

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
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), [](const auto &polygon) {
    return getArea(polygon);
  });
  return areas;
}

std::vector< double > anikanov::getAreasIf(const polygonArr &polygons, funcShema func)
{
  std::vector< double > areas;
  for (const auto &polygon: polygons) {
    if (func(polygon)) {
      areas.push_back(getArea(polygon));
    }
  }
  return areas;
}

std::vector< size_t > anikanov::getVertexes(const polygonArr &polygons)
{
  std::vector< size_t > vertexes;
  for (const auto &polygon: polygons) {
    vertexes.push_back(polygon.points.size());
  }
  return vertexes;
}

void anikanov::area(const polygonArr &polygons, std::istream &in, std::ostream &out)
{
  std::string subcmd;
  in >> subcmd;
  std::vector< double > areas;
  if (subcmd == "ODD") {
    areas = getAreasIf(polygons, [](const Polygon &pol) {
      return pol.points.size() % 2 == 1;
    });
  } else if (subcmd == "EVEN") {
    areas = getAreasIf(polygons, [](const Polygon &pol) {
      return pol.points.size() % 2 == 0;
    });
  } else if (subcmd == "MEAN") {
    areas = getAreas(polygons);
    double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
    if (polygons.empty()) {
      throw std::runtime_error("Invalid command");
    }
    out << std::fixed << std::setprecision(1) << sum / static_cast< double >(polygons.size()) << "\n";
    return;
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
      return pol.points.size() == count;
    });
  }
  out << std::accumulate(areas.begin(), areas.end(), 0.0) << "\n";
  return;
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

void anikanov::count(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  size_t count;
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "ODD") {
    count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
      return pol.points.size() % 2 == 1;
    });
  } else if (subcmd == "EVEN") {
    count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
      return pol.points.size() % 2 == 0;
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
      return pol.points.size() == specificNumber;
    });
  }
  out << count << "\n";
}

bool anikanov::isRightAngle(const anikanov::Point &A, const anikanov::Point &B, const anikanov::Point &C)
{
  double AB = getLenght(A, B);
  double BC = getLenght(B, C);
  double AC = getLenght(A, C);

  return std::abs(AB * AB + BC * BC - AC * AC) < 1e-9;
}

void anikanov::rects(const std::vector< Polygon > &polygons, std::istream &, std::ostream &out)
{
  out << std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
    if (pol.points.size() != 4) {
      return false;
    }

    double side1 = getLenght(pol.points[0], pol.points[1]);
    double side2 = getLenght(pol.points[1], pol.points[2]);
    double side3 = getLenght(pol.points[2], pol.points[3]);
    double side4 = getLenght(pol.points[3], pol.points[0]);

    return side1 == side3 && side2 == side4 && isRightAngle(pol.points[0], pol.points[1], pol.points[2]);
  }) << "\n";
}

bool anikanov::hasRightAngle(const anikanov::Polygon &polygon, size_t index)
{
  if (index == polygon.points.size()) {
    return false;
  }

  if (isRightAngle(polygon.points[index], polygon.points[(index + 1) % polygon.points.size()],
                   polygon.points[(index + 2) % polygon.points.size()])) {
    return true;
  }

  return anikanov::hasRightAngle(polygon, index + 1);
}

void anikanov::rightShapes(const std::vector< Polygon > &polygons, std::istream &, std::ostream &out)
{
  out << std::count_if(polygons.begin(), polygons.end(), [](const Polygon &pol) {
    return anikanov::hasRightAngle(pol);
  }) << "\n";
}
