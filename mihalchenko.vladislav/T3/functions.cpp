#include "functions.hpp"
// #include <iostream>
#include <iomanip>
#include <cmath>
// #include <stdexcept>
#include <numeric>
// #include <algorithm>
// #include <functional>
// #include "mapOfCommands.hpp"
#include <scopeGuard.hpp>
#include <delimiters.hpp>

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
  auto triangleArea = getPoints(startPoint, nextPoint);
  return area += triangleArea;
}

double mihalchenko::countArea(const Polygon &polygon)
{
  double area = std::accumulate(polygon.points.begin(),
                                std::prev(polygon.points.end()), 0.,
                                sumArea);
  auto lhs = std::prev(polygon.points.end())->x * polygon.points.front().y;
  auto rhs = polygon.points.front().x * std::prev(polygon.points.end())->y;
  auto pmArea = lhs - rhs;
  area = 0.5 * std::abs(area + pmArea);
  return area;
}

void mihalchenko::getAreaOdd(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyOddPolygons;
  std::copy_if(polygons.cbegin(), polygons.cend(),
               std::back_inserter(copyOddPolygons),
               std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2));
  getAreaResult(copyOddPolygons, false, out);
}

void mihalchenko::getAreaEven(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyEvenPolygons;
  std::copy_if(polygons.cbegin(),
               polygons.cend(),
               std::back_inserter(copyEvenPolygons),
               std::bind(std::logical_not<bool>{},
                         std::bind(std::bind(std::modulus<size_t>{},
                                             std::bind(getSize, _1), 2),
                                   _1)));
  getAreaResult(copyEvenPolygons, false, out);
}

void mihalchenko::getAreaMean(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<Polygon> copyPolygons;
  std::copy(polygons.cbegin(),
            polygons.cend(),
            std::back_inserter(copyPolygons));
  getAreaResult(copyPolygons, true, out);
}

void mihalchenko::getAreaVertexes(const std::vector<Polygon> &polygons,
                                  size_t num, std::ostream &out)
{
  std::vector<Polygon> copyPolygonIfEqual;
  std::copy_if(
      polygons.cbegin(),
      polygons.cend(),
      std::back_inserter(copyPolygonIfEqual),
      std::bind(std::bind(std::equal_to<size_t>{}, std::bind(getSize, _1), _2), _1, num));
  getAreaResult(copyPolygonIfEqual, false, out);
}

std::ostream &mihalchenko::getAreaResult(const std::vector<Polygon> &copyPolygons,
                                         bool isMeanPredicate, std::ostream &out)
{
  iofmtguard fmtguard(out);
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

void mihalchenko::printArea(const std::vector<Polygon> &polygons, std::istream &is,
                            std::ostream &out)
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

int mihalchenko::getNumOfVertexes(const Polygon &polygons)
{
  return polygons.points.size();
}

std::ostream &mihalchenko::getMaxArea(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<double> areas(polygons.size());
  // areas.reserve(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), countArea);
  double maxArea = *std::max_element(areas.cbegin(), areas.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << maxArea << '\n';
  return out;
}

std::ostream &mihalchenko::getMaxVertexes(const std::vector<Polygon> &polygons, std::ostream &out)
{
  // std::vector<int> numsOfVertexes(polygons.size());
  std::vector<int> numsOfVertexes(polygons.size());
  // numsOfVertexes.resize(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::max_element(numsOfVertexes.cbegin(), numsOfVertexes.cend());
  out << maxVertexes << '\n';
  return out;
}

void mihalchenko::printMax(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "AREA")
  {
    getMaxArea(polygons, out);
  }
  else if (partOfCmd == "VERTEXES")
  {
    getMaxVertexes(polygons, out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

std::ostream &mihalchenko::getMinArea(const std::vector<Polygon> &polygons, std::ostream &out)
{
  std::vector<double> areas(polygons.size());
  // areas.reserve(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), countArea);
  double maxArea = *std::min_element(areas.cbegin(), areas.cend());
  iofmtguard fmtguard(out);
  out << std::fixed << std::setprecision(1);
  out << maxArea << '\n';
  return out;
}

std::ostream &mihalchenko::getMinVertexes(const std::vector<Polygon> &polygons, std::ostream &out)
{
  // std::vector<int> numsOfVertexes(polygons.size());
  std::vector<int> numsOfVertexes(polygons.size());
  // numsOfVertexes.resize(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), numsOfVertexes.begin(), getNumOfVertexes);
  int maxVertexes = *std::min_element(numsOfVertexes.cbegin(), numsOfVertexes.cend());
  out << maxVertexes << '\n';
  return out;
}

void mihalchenko::printMin(const std::vector<Polygon> &polygons, std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "AREA")
  {
    getMinArea(polygons, out);
  }
  else if (partOfCmd == "VERTEXES")
  {
    getMinVertexes(polygons, out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

std::ostream &mihalchenko::countOdd(const std::vector<Polygon> &polygons, std::ostream &out)
{
  out << std::count_if(polygons.cbegin(),
                       polygons.cend(),
                       std::bind(std::modulus<size_t>{}, std::bind(getSize, _1), 2))
      << '\n';
  return out;
}

std::ostream &mihalchenko::countEven(const std::vector<Polygon> &polygons, std::ostream &out)
{
  out << std::count_if(polygons.cbegin(), polygons.cend(),
                       std::bind(std::logical_not<bool>{},
                                 std::bind(std::bind(std::modulus<size_t>{},
                                                     std::bind(getSize, _1), 2),
                                           _1)))
      << '\n';
  return out;
}

std::ostream &mihalchenko::countVertexes(const std::vector<Polygon> &polygons,
                                         size_t num, std::ostream &out)
{
  out << std::count_if(polygons.cbegin(),
                       polygons.cend(),
                       std::bind(std::bind(std::equal_to<size_t>{},
                                           std::bind(getSize, _1), _2),
                                 _1, num))
      << '\n';
  return out;
}

void mihalchenko::printCount(const std::vector<Polygon> &polygons,
                             std::istream &is, std::ostream &out)
{
  std::string partOfCmd;
  is >> partOfCmd;
  if (partOfCmd == "EVEN")
  {
    countEven(polygons, out);
  }
  else if (partOfCmd == "ODD")
  {
    countOdd(polygons, out);
  }
  else if ((partOfCmd[0]) && stoull(partOfCmd) >= 3)
  {
    countVertexes(polygons, stoull(partOfCmd), out);
  }
  else
  {
    throw std::logic_error("Something wrong...");
  }
}

long long mihalchenko::getLength(const Polygon &polygon)
{
  return polygon.points.size();
}

bool mihalchenko::isLengthCorrect(const Polygon &lhsPolygon, const Polygon &rhsPolygon)
{
  if (lhsPolygon.points.size() == std::count_if(rhsPolygon.points.begin(),
                                                rhsPolygon.points.end(),
                                                std::bind(arePointsCorrect,
                                                          lhsPolygon, _1)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool mihalchenko::isPointCorrect(const Point &lhsPoint, const Point &rhsPoint)
{
  if (((lhsPoint.x == rhsPoint.x) && (lhsPoint.y == rhsPoint.y)) ||
      ((lhsPoint.x == rhsPoint.y) && (lhsPoint.y == rhsPoint.x)))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool mihalchenko::arePointsCorrect(const Polygon &polygon, const Point &point)
{
  return std::find_if(polygon.points.begin(),
                      polygon.points.end(),
                      std::bind(isPointCorrect, point, _1)) != polygon.points.end();
}

void mihalchenko::printPerms(const std::vector<Polygon> &polygons,
                             std::istream &is, std::ostream &out)
{
  Polygon copyPolygon;
  is >> copyPolygon;
  size_t numOfVertexes = copyPolygon.points.size();
  std::vector<Polygon> copyVectorOfPolygons;
  copy_if(polygons.begin(),
          polygons.end(),
          std::back_inserter(copyVectorOfPolygons),
          std::bind(std::equal_to<size_t>{},
                    std::bind(getLength, _1), numOfVertexes));
  if (!copyVectorOfPolygons.empty())
  {
    out << std::count_if(polygons.begin(),
                         polygons.end(),
                         std::bind(isLengthCorrect, copyPolygon, _1))
        << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>" << '\n';
  }
}

mihalchenko::Point mihalchenko::getVector(const Point &lhsPoint, const Point &rhsPoint)
{
  return Point{rhsPoint.x - lhsPoint.x, rhsPoint.y - lhsPoint.y};
}

double mihalchenko::getCos(const Point &lhsVect, const Point &rhsVect)
{
  double scalarProduct = lhsVect.x * rhsVect.x + rhsVect.y * rhsVect.y;
  double lengthOfLhsVector = sqrt(pow(lhsVect.x, 2) + pow(lhsVect.y, 2));
  double lengthOfRhsVector = sqrt(pow(rhsVect.x, 2) + pow(rhsVect.y, 2));
  return scalarProduct / (lengthOfLhsVector * lengthOfRhsVector);
}

bool mihalchenko::isZeroCos(const double &cos)
{
  return cos == 0;
}

bool mihalchenko::isRightPolygon(const Polygon &polygon)
{
  std::vector<Point> vectorOfPoints;

  std::transform(
      polygon.points.cbegin(),
      std::prev(polygon.points.cend()),
      std::next(polygon.points.cbegin()),
      std::back_inserter(vectorOfPoints),
      std::bind(getVector, _1, _2));
  vectorOfPoints.push_back(std::bind(getVector, _1, _2)(polygon.points.back(),
                                                        polygon.points.front()));
  std::vector<double> cosOfVectors;
  std::transform(
      vectorOfPoints.cbegin(),
      std::prev(vectorOfPoints.cend()),
      std::next(vectorOfPoints.cbegin()),
      std::back_inserter(cosOfVectors),
      std::bind(getCos, _1, _2));
  cosOfVectors.push_back(std::bind(getCos, _1, _2)(vectorOfPoints.back(),
                                                   vectorOfPoints.front()));
  return std::find_if(
             cosOfVectors.cbegin(),
             cosOfVectors.cend(),
             isZeroCos) != cosOfVectors.cend();
  /*return std::bind(std::bind(std::not_equal_to<size_t>{}, std::find_if(cosOfVectors.begin(),
             cosOfVectors.end(), std::bind(getVector, _1), _2), _1, cosOfVectors.end()));*/
}

void mihalchenko::countRightShapes(const std::vector<Polygon> &polygons, std::ostream &out)
{
  out << std::count_if(polygons.cbegin(), polygons.cend(), isRightPolygon) << '\n';
}
