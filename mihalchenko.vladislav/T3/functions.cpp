#include "functions.hpp"
// #include <iostream>
#include <iomanip>
#include <cmath>
// #include <stdexcept>
#include <numeric>
#include <algorithm>
#include <functional>
// #include "mapOfCommands.hpp"

// using namespace mihalchenko;
using namespace std::placeholders;

size_t mihalchenko::getSize(const Polygon &polygon)
{
  return polygon.points.size();
}

double mihalchenko::sumArea(double area, const Point &startPoint)
{
  auto nextPoint = *std::next(&startPoint);
  auto triangleArea = ((startPoint.x * nextPoint.y) - (nextPoint.x * startPoint.y));
  auto newArea = area + triangleArea;
  return newArea;
}

double mihalchenko::countArea(const Polygon &polygon)
{
  double area = std::accumulate(polygon.points.begin(), std::prev(polygon.points.end()), 0., sumArea);
  auto lhs = std::prev(polygon.points.end())->x * polygon.points.front().y;
  auto rhs = polygon.points.front().x * std::prev(polygon.points.end())->y;
  auto pmArea = lhs - rhs;
  area = 0.5 * std::abs(area + pmArea);
  return area;
}

void mihalchenko::printAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyEvenPolygons;
  // Polygon polygon = *copyEvenPolygons.begin();
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(copyEvenPolygons), std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2));
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(copyEvenPolygons.begin(), copyEvenPolygons.end(), 0., std::bind(std::plus<double>{}, _1, std::bind(countArea, _2)));
}

void mihalchenko::printAreaEven(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyOddPolygons;
  Polygon polygon = *copyOddPolygons.begin();
  std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(copyOddPolygons), std::bind(std::logical_not<bool>{}, std::bind(std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2), _1)));
  out << std::fixed << std::setprecision(1);
  out << std::accumulate(copyOddPolygons.begin(), copyOddPolygons.end(), 0., std::bind(std::plus<double>{}, _1, std::bind(countArea, _2)));
}
