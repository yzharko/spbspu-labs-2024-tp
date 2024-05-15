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
#include "commands.hpp"

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

void kovshikov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(kovshikov::getAreaEven, _1, _2);
    area["ODD"] = std::bind(kovshikov::getAreaOdd, _1, _2);
    area["MEAN"] = std::bind(kovshikov::getAreaMean, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    area.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
   /* if(std::all_of(command.begin(), command.end(), isDigit) == true)
    {
      unsigned long long num = std::stoll(command);
      if(num < 3)
      {
        throw;
      }
      getAreaVertex(num, allData, out);
    }
    else
    {
      throw;
    }*/
    getCheck(command, getAreaVertex, allData, out);
  }
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

void kovshikov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), isEven);
  double area = std::accumulate(even.begin(), even.end(), 0, resultArea);
  out << area << "\n";
}

void kovshikov::getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), isOdd);
  double area = std::accumulate(odd.begin(), odd.end(), 0, resultArea);
  out << area << "\n";
}

void kovshikov::getAreaMean(const std::vector< Polygon >& allData, std::ostream& out)
{
  fileIsEmpty(allData);
  double area = std::accumulate(allData.begin(), allData.end(), 0, resultArea);
  double result = area / allData.size();
  out << result << "\n";
}

bool kovshikov::isThisVertex(unsigned long long num, Polygon polygon)
{
  return polygon.points.size() == num;
}

void kovshikov::getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  double result = 0;
  if(allData.empty())
  {
    out << result << "\n";
  }
  else
  {
    using namespace std::placeholders;
    std::vector< Polygon >::const_iterator detected = std::find_if(allData.begin(), allData.end(), std::bind(isThisVertex, num, _1));
    int count = std::count_if(allData.begin(), allData.end(), std::bind(isThisVertex, num, _1));
    if(detected == allData.end())
    {
      out << result << "\n";
    }
    result = countArea(*detected) * count;
    out << result << "\n";
  }
}

void kovshikov::getMax(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > max;
  {
    using namespace std::placeholders;
    max["AREA"] = std::bind(kovshikov::getMaxArea, _1, _2);
    max["VERTEXES"] = std::bind(kovshikov::getMaxVertexes, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    fileIsEmpty(allData);
    max.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    throw;
  }
}

void kovshikov::getMaxArea(const std::vector< Polygon >& allData, std::ostream& out)
{
  double maxArea = 0;
  std::vector< double > allAreas;
  std::transform(allData.begin(), allData.end(), std::back_inserter(allAreas), countArea);
  std::sort(allAreas.begin(), allAreas.end());
  maxArea = *(allAreas.end() - 1);
  out << maxArea << "\n";
}

unsigned long long kovshikov::getVertexes(const Polygon& polygon)
{
  return polygon.points.size();
}

void kovshikov::getMaxVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long maxVertexes = 0;
  std::vector< unsigned long long > allVertexes;
  std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertexes);
  std::sort(allVertexes.begin(), allVertexes.end());
  maxVertexes = *(allVertexes.end() - 1);
  out << maxVertexes << "\n";
}

void kovshikov::getMin(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > min;
  {
    using namespace std::placeholders;
    min["AREA"] = std::bind(kovshikov::getMinArea, _1, _2);
    min["VERTEXES"] = std::bind(kovshikov::getMinVertexes, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    min.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    throw;
  }
}

void kovshikov::getMinArea(const std::vector< Polygon >& allData, std::ostream& out)
{
  double minArea = 0;
  if(allData.empty())
  {
    out << minArea << "\n";
  }
  else
  {
    std::vector< double > allAreas;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allAreas), countArea);
    std::sort(allAreas.begin(), allAreas.end());
    minArea = *(allAreas.begin());
    out << minArea << "\n";
  }
}

void kovshikov::getMinVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long minVertexes = 0;
  if(allData.empty())
  {
    out << minVertexes << "\n";
  }
  else
  {
    std::vector< unsigned long long > allVertexes;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertexes);
    std::sort(allVertexes.begin(), allVertexes.end());
    minVertexes = *(allVertexes.begin());
    out << minVertexes << "\n";
  }
}

void kovshikov::count(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > count;
  {
    using namespace std::placeholders;
    count["EVEN"] = std::bind(kovshikov::countEven, _1, _2);
    count["ODD"] = std::bind(kovshikov::countOdd, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    count.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    if(std::all_of(command.begin(), command.end(), isDigit) == true)
    {
      unsigned long long num = std::stoll(command);
      if(num < 3)
      {
        throw;
      }
      countVertexes(num, allData, out);
    }
    else
    {
      throw;
    }
  }
}

void kovshikov::countEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), isEven);
  unsigned long long count = even.size();
  out << count << "\n";
}

void kovshikov::countOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), isOdd);
  unsigned long long count = odd.size();
  out << count << "\n";
}

void kovshikov::countVertexes(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long count = 0;
  std::vector< Polygon > withThisVertexes;
  using namespace std::placeholders;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(withThisVertexes), std::bind(isThisVertex, num, _1));
  count = withThisVertexes.size();
  out << count << "\n";
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

void kovshikov::countRightshapes(const std::vector< Polygon >& allData, std::ostream& out)
{
  out << std::count_if(allData.begin(), allData.end(), isPolygonRight) << "\n";
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

void kovshikov::checkInframe(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  Polygon polygon;
  is >> polygon;
  if(!is)
  {
    throw std::out_of_range("");
  }
  else
  {
    bool check = isInframe(allData, polygon);
    if(check == true)
    {
      out << "<TRUE>" << "\n";
    }
    else
    {
      out << "<FALSE>" << "\n";
    }
  }
}

void kovshikov::outputError(std::ostream& out, const std::string& strError)
{
  out << strError << "\n";
}
