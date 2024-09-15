#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

std::ostream& popov::getArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string parametr = "";
  in >> parametr;
  if (parametr == "EVEN")
  {
    out << std::fixed << std::setprecision(1) << getAreaEven(polygons) << '\n';
  }
  else if (parametr == "ODD")
  {
    out << std::fixed << std::setprecision(1) << getAreaOdd(polygons) << '\n';
  }
  else if (parametr == "MEAN")
  {
    out << std::fixed << std::setprecision(1) << getAreaMean(polygons) << '\n';
  }
  else
  {
    int numOfVertexes = std::stoi(parametr);
    out << std::fixed << std::setprecision(1) << getAreaVertexes(polygons, numOfVertexes) << '\n';
  }
  return out;
}

double popov::getAreaEven(const std::vector< Polygon > & polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  std::vector< Polygon > polygon;
  std::copy_if
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygon),
    isPolygonEven);
  std::vector< double > sums = getAreas(polygon);
  double sum = std::accumulate(sums.begin(), sums.end(), 0.0);
  return sum;
}

bool popov::isPolygonEven(const Polygon& polygon) {
  return polygon.points.size() % 2 == 0;
}

double popov::getAreaOdd(const std::vector< Polygon > & polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  std::vector< Polygon > oddPolygon;
  std::copy_if
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(oddPolygon),
    isPolygonOdd
  );
  std::vector< double > sums = getAreas(oddPolygon);
  double sum = std::accumulate(sums.begin(), sums.end(), 0.0);
  return sum;
}

bool popov::isPolygonOdd(const Polygon& polygon) {
  return polygon.points.size() % 2 != 0;
}

double popov::getAreaMean(const std::vector< Polygon > & polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("not enough data");
  }
  std::vector< double > sums = getAreas(polygons);
  double sum = std::accumulate(sums.begin(), sums.end(), 0.0);
  return sum / polygons.size();
}

std::vector< double > popov::getAreas(const std::vector< Polygon > & polygons)
{
  std::vector< double > areas;
  std::transform
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(areas),
    std::bind(calculateAreaAndPushBack, std::placeholders::_1)
  );
  return areas;
}

double popov::calculateAreaAndPushBack(const Polygon& polygon) {
  double area = getsArea(polygon);
  return area;
}

double popov::getsArea(const Polygon & polygon)
{
  if (polygon.points.size() < 3) {
    return 0.0;
  }
  double area = std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0,
    [&](double sum, const Point& p) {
      return accumulateArea(sum, p, polygon.points);
    }
  );
  return std::abs(area) / 2.0;
}

double popov::calculateArea(const Point& p1, const Point& p2) {
  return (p1.x * p2.y - p2.x * p1.y);
}

double popov::accumulateArea(double sum, const Point& p, const std::vector<Point>& polygon)
{
  auto nextIt = std::next(std::find(polygon.begin(), polygon.end(), p));
  if (p == polygon.end()) {
    nextIt = polygon.begin();
  }
  return sum + calculateArea(p, *nextIt);
}

double popov::getAreaVertexes(const std::vector< Polygon > & polygons, int num)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  std::vector< Polygon > filteredPolygons;
  std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(filteredPolygons),
      std::bind(hasNumVertexes, std::placeholders::_1, num)
  );
  std::vector< double > areas = getAreas(filteredPolygons);
  double sum = std::accumulate(areas.begin(), areas.end(), 0.0);
  return sum;
}

bool popov::hasNumVertexes(const Polygon& polygon, int num) {
  return polygon.points.size() == static_cast<size_t>(num);
}

std::ostream& popov::maxCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string parametr = "";
  in >> parametr;
  if (parametr == "AREA")
  {
    std::vector< double > areaV = maxArea(polygons);
    double area = *std::max_element(areaV.begin(), areaV.end());
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (parametr == "VERTEXES")
  {
    std::vector< int > vert = maxVertexes(polygons);
    int vertex = *std::max_element(vert.begin(), vert.end());
    out << vertex << '\n';
  }
  return out;
}

std::vector< double > popov::maxArea(const std::vector< Polygon >& polygons)
{
  std::vector< double > areas;
  std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(areas),
      std::bind(calculatingArea, std::placeholders::_1)
  );
  return areas;
}

double popov::calculatingArea(const Polygon& polygon) {
  return getsArea(polygon);
}

std::vector< int > popov::maxVertexes(const std::vector< Polygon >& polygons)
{
  std::vector< int > vert;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vert),
    std::bind(numOfVertexes, std::placeholders::_1)
  );
  return vert;
}

int popov::numOfVertexes(const Polygon & polygon)
{
  return polygon.points.size();
}

std::ostream& popov::minCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string parametr = "";
  in >> parametr;
  if (parametr == "AREA")
  {
    std::vector< double > areaV = maxArea(polygons);
    double area = *std::min_element(areaV.begin(), areaV.end());
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (parametr == "VERTEXES")
  {
    std::vector< int > vert = maxVertexes(polygons);
    int vertex = *std::min_element(vert.begin(), vert.end());
    out << vertex << '\n';
  }
  return out;
}

std::ostream& popov::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string parametr = "";
  in >> parametr;
  if (parametr == "EVEN")
  {
    out << evenCount(polygons) << '\n';
  }
  else if (parametr == "ODD")
  {
    out << oddCount(polygons) << '\n';
  }
  else
  {
    int numOfVertexes = std::stoi(parametr);
    out << vertCount(polygons, numOfVertexes) << '\n';
  }
  return out;
}

int popov::evenCount(const std::vector< Polygon >& polygons)
{
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    isPolygonEven
  );
}

int popov::oddCount(const std::vector< Polygon >& polygons)
{
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    isPolygonOdd
  );
}

int popov::vertCount(const std::vector< Polygon >& polygons, int n)
{
  if (n < 3)
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  return std::count_if(
    polygons.begin(),
    polygons.end(),
    std::bind(hasNumVertexes, std::placeholders::_1, n)
  );
}

std::ostream& popov::inframe(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon specPolyg;
  in >> specPolyg;
  std::pair<Point, Point> frame = findMinMaxXY(polygons);
  int specMinX = getMinX(specPolyg);
  int specMinY = getMinY(specPolyg);
  int specMaxX = getMaxX(specPolyg);
  int specMaxY = getMaxY(specPolyg);
  if ((specMinX >= frame.first.x) and (specMinY >= frame.first.y) and (specMaxX <= frame.second.x) and (specMaxY <= frame.second.y))
  {
    out << "<TRUE>" << "\n";
  }
  else
  {
    out << "<FALSE>" << "\n";
  }
  return out;
}

std::pair<popov::Point, popov::Point> popov::findMinMaxXY(const std::vector< Polygon >& polygons)
{
  std::vector< int > minXV(polygons.size());
  std::transform(polygons.begin(), polygons.end(), minXV.begin(), minPolygonX);
  int minX = *std::min_element(minXV.begin(), minXV.end());

  std::vector< int > maxXV(polygons.size());
  std::transform(polygons.begin(), polygons.end(), maxXV.begin(), maxPolygonX);
  int maxX = *std::max_element(maxXV.begin(), maxXV.end());

  std::vector< int > minYV(polygons.size());
  std::transform(polygons.begin(), polygons.end(), minYV.begin(), minPolygonY);
  int minY = *std::min_element(minYV.begin(), minYV.end());

  std::vector< int > maxYV(polygons.size());
  std::transform(polygons.begin(), polygons.end(), maxYV.begin(), maxPolygonY);
  int maxY = *std::max_element(maxYV.begin(), maxYV.end());
  return std::make_pair(Point{minX, minY}, Point{maxX, maxY});
}

int popov::minPolygonX(const Polygon& polygon)
{
  auto min = std::min_element(polygon.points.begin(), polygon.points.end(), compareX);
  return (*min).x;
}

int popov::minPolygonY(const Polygon& polygon)
{
  auto min = std::min_element(polygon.points.begin(), polygon.points.end(), compareY);
  return (*min).y;
}

int popov::maxPolygonX(const Polygon& polygon)
{
  auto max = std::max_element(polygon.points.begin(), polygon.points.end(), compareX);
  return (*max).x;
}

int popov::maxPolygonY(const Polygon& polygon)
{
  auto max = std::max_element(polygon.points.begin(), polygon.points.end(), compareY);
  return (*max).y;
}

bool popov::compareX(const Point& p1, const Point& p2)
{
  return p1.x < p2.x;
}

bool popov::compareY(const Point& p1, const Point& p2)
{
  return p1.y < p2.y;
}

int popov::getMinX(const Polygon& polygon)
{
  auto minXIter = std::min_element(
    polygon.points.begin(),
    polygon.points.end(),
    compareX
  );
  return (*minXIter).x;
}

int popov::getMinY(const Polygon& polygon)
{
  auto minYIter = std::min_element(
    polygon.points.begin(),
    polygon.points.end(),
    compareY
  );
  return (*minYIter).y;
}

int popov::getMaxX(const Polygon& polygon)
{
  auto maxXIter = std::max_element(
    polygon.points.begin(),
    polygon.points.end(),
    compareX
  );
  return (*maxXIter).x;
}

int popov::getMaxY(const Polygon& polygon)
{
  auto maxYIter = std::max_element(
    polygon.points.begin(),
    polygon.points.end(),
    compareY
  );
  return (*maxYIter).y;
}

std::ostream& popov::maxSeq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polyg;
  in >> polyg;
  if (polygons.empty() or (polyg.points.size() < 3))
  {
    throw std::logic_error("");
  }
  std::vector< int > maxSeq;
  int counter = 0;
  auto multiplyFunction = [&counter, &polyg](const Polygon& polygon) {
        return countSeq(polygon, polyg, counter);
  };
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(maxSeq), multiplyFunction);
  int max = *std::max_element(maxSeq.begin(), maxSeq.end());
  out << max << "\n";
  return out;
}

int popov::countSeq(const popov::Polygon& polygon, const popov::Polygon& polyg, int& counter)
{
  if (polygon == polyg)
  {
    counter++;
  }
  else
  {
    counter = 0;
  }
  return counter;
}

bool popov::operator==(const Polygon& p1, const Polygon& p2)
{
  if (p1.points.size() != p2.points.size())
  {
    return false;
  }
  return p1.points == p2.points;
}

bool popov::operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

void popov::invalidMessage(std::ostream& out)
{
  out << "<INVALID COMMAND>" << "\n";
}
