#include "for_commands.hpp"
#include <algorithm>
#include <cstring>
#include <functional>
#include <fstream>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <numeric>
#include "polygons.hpp"

void kovshikov::fileIsEmpty(const std::vector< Polygon >& allData)
{
  if(allData.empty())
  {
    throw std::out_of_range("");
  }
}

bool kovshikov::isDigit(char ch)
{
  return std::isdigit(ch);
}

void kovshikov::getCheck(std::string command,
                           void(*getFunction)(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out),
                             const std::vector< Polygon >& allData, std::ostream& out)
{
  if(std::all_of(command.begin(), command.end(), isDigit) == true)
  {
    unsigned long long num = std::stoll(command);
    if(num < 3)
    {
      throw std::out_of_range("");
    }
    getFunction(num, allData, out);
  }
  else
  {
    throw std::out_of_range("");
  }
}

int kovshikov::getCordMethod(const Point& currentPoint,const Point& prevPoint)
{
  int currentX = currentPoint.x;
  int currentY = currentPoint.y;
  int prevX = prevPoint.x;
  int prevY = prevPoint.y;
  int area = (prevX + currentX) * (prevY - currentY);
  return area;
}

double kovshikov::countArea(const Polygon polygon)
{
  int area = 0;
  std::vector< int > areas(polygon.points.size());
  std::vector< int >::iterator startAreas = areas.begin();
  std::vector< int >::iterator finishAreas = areas.end();

  std::vector< Point >::const_iterator finish = polygon.points.end();
  std::vector< Point >::const_iterator prevPoint = polygon.points.begin();
  std::vector< Point >::const_iterator currentPoint = polygon.points.begin() + 1;

  std::transform(currentPoint, finish, prevPoint, startAreas, getCordMethod);
  *(finishAreas - 1) = getCordMethod(*prevPoint, *(finish - 1));

  area = std::accumulate(startAreas, finishAreas, 0);
  return std::abs(area / 2.0);
}

double kovshikov::resultArea(double summa, const Polygon polygon)
{
  summa += countArea(polygon);
  return summa;
}

bool kovshikov::isEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool kovshikov::isOdd(const Polygon& polygon)
{
  return !isEven(polygon);
}

bool kovshikov::isThisVertex(unsigned long long num, Polygon polygon)
{
  return polygon.points.size() == num;
}

unsigned long long kovshikov::getVertexes(const Polygon& polygon)
{
  return polygon.points.size();
}

kovshikov::Point kovshikov::createVector(const Point& next, const Point& current)
{
  int vectorX = next.x - current.x;
  int vectorY = next.y - current.y;
  return Point{vectorX, vectorY};
}

int kovshikov::getScalar(const Point& next, const Point& current)
{
  return (next.x * current.x) + (next.y * current.y);
}

bool kovshikov::isRight(int scalar)
{
  if(scalar == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool kovshikov::isPolygonRight(const Polygon& polygon)
{
  std::vector< Point > allVectors;
  std::vector< int > allScalars;
  std::vector< Point >::const_iterator next = polygon.points.begin() + 1;
  std::vector< Point >::const_iterator current = polygon.points.begin();
  std::transform(next, polygon.points.end(), current, std::back_inserter(allVectors), createVector);
  allVectors.push_back(createVector(polygon.points.front(), polygon.points.back()));
  std::transform(allVectors.begin() + 1, allVectors.end(), allVectors.begin(), std::back_inserter(allScalars), getScalar);
  allScalars.push_back(getScalar(allVectors.front(), allVectors.back()));
  return std::any_of(allScalars.begin(), allScalars.end(), isRight);
}

int kovshikov::getX(const Point& point)
{
  return point.x;
}

int kovshikov::getY(const Point& point)
{
  return point.y;
}

int kovshikov::getMaxCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
  std::vector< int > coordinates;
  std::transform(polygon.points.begin(), polygon.points.end(), std::back_inserter(coordinates), getCoordinate);
  int max = *std::max_element(coordinates.begin(), coordinates.end());
  return max;
}

int kovshikov::getMinCoordinate(const Polygon& polygon, int(*getCoordinate)(const Point& point))
{
  std::vector< int > coordinates;
  std::transform(polygon.points.begin(), polygon.points.end(), std::back_inserter(coordinates), getCoordinate);
  int min = *std::min_element(coordinates.begin(), coordinates.end());
  return min;
}

std::vector< kovshikov::Point > kovshikov::getFrame(const std::vector< Polygon >& allData)
{
  std::vector< int > allMaxX;
  std::vector< int > allMaxY;
  std::vector< int > allMinX;
  std::vector< int > allMinY;
  using namespace std::placeholders;
  std::transform(allData.begin(), allData.end(), std::back_inserter(allMaxX), std::bind(getMaxCoordinate, _1, getX));
  std::transform(allData.begin(), allData.end(), std::back_inserter(allMaxY), std::bind(getMaxCoordinate, _1, getY));
  std::transform(allData.begin(), allData.end(), std::back_inserter(allMinX), std::bind(getMinCoordinate, _1, getX));
  std::transform(allData.begin(), allData.end(), std::back_inserter(allMinY), std::bind(getMinCoordinate, _1, getY));
  int maxX = *std::max_element(allMaxX.begin(), allMaxX.end());
  int maxY = *std::max_element(allMaxY.begin(), allMaxY.end());
  int minX = *std::min_element(allMinX.begin(), allMinX.end());
  int minY = *std::min_element(allMinY.begin(), allMinY.end());
  std::vector < Point > frame;
  frame.push_back(Point{minX, maxY});
  frame.push_back(Point{maxX, maxY});
  frame.push_back(Point{maxX, minY});
  frame.push_back(Point{minX, minY});
  return frame;
}

bool kovshikov::isInframe(const std::vector< Polygon >& allData, const Polygon& polygon)
{
  std::vector< Point > frame = getFrame(allData);
  int maxFrameX = frame[1].x;
  int minFrameX = frame[0].x;
  int maxFrameY = frame[0].y;
  int minFrameY = frame[2].y;
  int maxPolygonX = getMaxCoordinate(polygon, getX);
  int minPolygonX = getMinCoordinate(polygon, getX);
  int maxPolygonY = getMaxCoordinate(polygon, getY);
  int minPolygonY = getMinCoordinate(polygon, getY);
  bool noMoreMax = maxPolygonX <= maxFrameX || maxPolygonY <= maxFrameY;
  bool noLessMin = minPolygonX >= minFrameX || minPolygonY >= minFrameY;
  if(noMoreMax && noLessMin)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void kovshikov::outputError(std::ostream& out)
{
  out << "<INVALID COMMAND>" << "\n";
}
