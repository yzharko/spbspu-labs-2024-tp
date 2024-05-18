#include "mainExtensions.hpp"

#include <algorithm>
#include <fstream>
#include <limits>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
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

double anikanov::max(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "AREA") {
    std::vector< double > areas = getAreas(polygons);
    auto maxAreaPolygon = *std::max_element(areas.begin(), areas.end());
    std::cout << std::fixed << std::setprecision(1) << maxAreaPolygon << '\n';
  } else if (subcmd == "VERTEXES") {
    std::vector< size_t > count = getVertexes(polygons);
    auto maxVertexesPolygon = *std::max_element(count.begin(), count.end());
    std::cout << std::fixed << std::setprecision(1) << maxVertexesPolygon << '\n';
  }
  throw std::runtime_error("Invalid command");
}

double anikanov::min(const std::vector< Polygon > &polygons, std::istream &in, std::ostream &out)
{
  std::string subcmd;
  in >> subcmd;
  if (subcmd == "AREA") {
    std::vector< double > areas = getAreas(polygons);
    auto minAreaPolygon = *std::min_element(areas.begin(), areas.end());
    std::cout << std::fixed << std::setprecision(1) << minAreaPolygon << '\n';
  } else if (subcmd == "VERTEXES") {
    std::vector< size_t > count = getVertexes(polygons);
    auto minVertexesPolygon = *std::min_element(count.begin(), count.end());
    std::cout << std::fixed << std::setprecision(1) << minVertexesPolygon << '\n';
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
      if (count < 3) {
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
