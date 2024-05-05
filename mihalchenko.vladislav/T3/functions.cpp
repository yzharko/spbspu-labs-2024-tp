#include "functions.hpp"
// #include <iostream>
#include <iomanip>
#include <cmath>
// #include <stdexcept>
#include <numeric>
// #include <algorithm>
// #include <functional>
// #include "mapOfCommands.hpp"

// using namespace mihalchenko;
using namespace std::placeholders;

size_t mihalchenko::getSize(const Polygon &polygon)
{
  return polygon.points.size();
}

double mihalchenko::getPoints(const Point &first, const Point &second)
{
  return first.x * second.y - first.y * second.x;
}

double mihalchenko::sumArea(double area, const Point &startPoint)
{
  auto nextPoint = *std::next(&startPoint);
  // auto triangleArea = ((startPoint.x * nextPoint.y) - (nextPoint.x * startPoint.y));
  auto triangleArea = getPoints(startPoint, nextPoint);
  // auto newArea = area + triangleArea;
  return area += triangleArea;
  // return newArea;
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

void mihalchenko::getAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyOddPolygons;
  // Polygon polygon = *copyEvenPolygons.begin();
  std::copy_if(polygons.cbegin(), polygons.cend(),
               std::back_inserter(copyOddPolygons),
               std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2));
  getAreaResult(copyOddPolygons, false, out);
}

void mihalchenko::getAreaEven(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyEvenPolygons;
  // Polygon polygon = *copyOddPolygons.begin();
  std::copy_if(polygons.cbegin(),
               polygons.cend(),
               std::back_inserter(copyEvenPolygons),
               std::bind(std::logical_not<bool>{}, std::bind(std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2), _1)));
  getAreaResult(copyEvenPolygons, false, out);
}

void mihalchenko::getAreaMean(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyPolygons;
  std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(copyPolygons));
  getAreaResult(copyPolygons, true, out);
}

void mihalchenko::getAreaVertexes(const std::vector<Polygon> &polygons, size_t num, std::ostream &out)
{
  std::vector<Polygon> copyPolygonIfEqual;
  std::copy_if(
      polygons.cbegin(), polygons.cend(), std::back_inserter(copyPolygonIfEqual),
      std::bind(std::bind(std::equal_to<size_t>{}, std::bind(getSize, _1), _2), _1, num));
  getAreaResult(copyPolygonIfEqual, false, out);
}

std::ostream &mihalchenko::getAreaResult(const std::vector<Polygon> &copyPolygons, bool isMeanPredicate, std::ostream &out)
{
  out << std::fixed << std::setprecision(1);
  if (isMeanPredicate == false)
  {
    out << std::accumulate(copyPolygons.begin(),
                           copyPolygons.end(), 0.,
                           std::bind(std::plus<double>{}, _1, std::bind(countArea, _2)));
  }
  else
  {
    out << std::accumulate(copyPolygons.begin(),
                           copyPolygons.end(), 0.,
                           std::bind(std::plus<double>{}, _1, std::bind(countArea, _2))) /
               copyPolygons.size();
  }
  return out << '\n';
}

void mihalchenko::printArea(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "EVEN")
  {
    getAreaEven(polygons, out);
  }
  else if (partOfCmd == "ODD")
  {
    getAreaOdd(polygons, out);
  }
  else if (partOfCmd == "MEAN")
  {
    getAreaMean(polygons, out);
  }
  else if (isdigit(partOfCmd[0]) && stoull(partOfCmd) >= 3)
  {
    getAreaVertexes(polygons, stoull(partOfCmd), out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}
