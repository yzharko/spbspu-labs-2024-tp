#include <numeric>
#include <iomanip>
#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "polygons.hpp"
#include "Commands.hpp"

void jirkov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(jirkov::getAreaEven, _1, _2);
    area["ODD"] = std::bind(jirkov::getAreaOdd, _1, _2);
    area["MEAN"] = std::bind(jirkov::getAreaMean, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    area.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    if(std::all_of(command.begin(), command.end(), isDigit) == true)
    {
      unsigned long long num = std::stoll(command);
      try
      {
        getAreaVertex(num, allData, out);
      }
      catch(const std::out_of_range& error)
      {
        throw;
      }
    }
    else
    {
      throw;
    }
  }
}

bool jirkov::isDigit(char ch)
{
  return std::isdigit(ch);
}

bool jirkov::findEven(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool jirkov::findOdd(const Polygon& polygon)
{
  return !findEven(polygon);
}

bool jirkov::findVertex(unsigned long long num, Polygon polygon)
{
  return polygon.points.size() == num;
}

void jirkov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), findEven);
  double area = std::accumulate(even.begin(), even.end(), 0, fullArea);
  out << area << "\n";
}

void jirkov::getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), findOdd);
  double area = std::accumulate(odd.begin(), odd.end(), 0, fullArea);
  out << area << "\n";
}

void jirkov::getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  using namespace std::placeholders;
  std::vector< Polygon >::const_iterator det = std::find_if(allData.begin(), allData.end(), std::bind(findVertex, num, _1));
  if(det == allData.end())
  {
    throw std::out_of_range("");
  }
  double res = countArea(*det);
  out << res << "\n";
}

void jirkov::getMax(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > max;
  {
    using namespace std::placeholders;
    max["AREA"] = std::bind(jirkov::getMaxArea, _1, _2);
    max["VERTEXES"] = std::bind(jirkov::getMaxVertexes, _1, _2);
  }
  std::string command;
  is >> command;
  try
  {
    max.at(command)(allData, out);
  }
  catch(const std::out_of_range& error)
  {
    throw;
  }
}

void jirkov::getMin(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > min;
  {
    using namespace std::placeholders;
    min["AREA"] = std::bind(jirkov::getMinArea, _1, _2);
    min["VERTEXES"] = std::bind(jirkov::getMinVertexes, _1, _2);
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
void jirkov::getMaxArea(const std::vector< Polygon >& allData, std::ostream& out)
{
  double maxArea = 0;
  if(allData.empty())
  {
    throw std::out_of_range("");
  }
  else
  {
    std::vector< double > allAreas;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allAreas), countArea);
    std::sort(allAreas.begin(), allAreas.end());
    maxArea = *(allAreas.end() - 1);
    out << maxArea << "\n";
  }
}

void jirkov::getMinArea(const std::vector< Polygon >& allData, std::ostream& out)
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

bool jirkov::findPerms(const Polygon & basePolygon, const Polygon & polygon)
{
  if (basePolygon.points.size() != polygon.points.size())
  {
    return false;
  }
    auto numOfPerms = std::count_if(
    basePolygon.points.begin(),
    basePolygon.points.end(),
    [polygon](const Point & cmpPoint)
    {
      return findEqual(cmpPoint, polygon);
    }
  );
  if (size_t(numOfPerms) == polygon.points.size())
  {
    return true;
  }
  return false;
}

void jirkov::checkPerms(const std::vector< Polygon > & allData, std::istream & is, std::ostream & out)
{
  Polygon basePolygon;
  is >> basePolygon;
  if (basePolygon.points.size() < 3)
  {
    throw std::exception();
  }
  out << std::fixed;
  using namespace std::placeholders;
  auto numPerms = std::count_if(
    allData.begin(),
    allData.end(),
    std::bind(findPerms, basePolygon, _1)
  );
  out << numPerms << "\n";
}

int jirkov::findCordinate(const Point& currentPoint,const Point& prevPoint)
{
  int currentX = currentPoint.x;
  int currentY = currentPoint.y;
  int prevX = prevPoint.x;
  int prevY = prevPoint.y;
  int area = (prevX + currentX) * (prevY - currentY);
  return area;
}

void jirkov::getAreaMean(const std::vector< Polygon >& allData, std::ostream& out)
{
  double area = std::accumulate(allData.begin(), allData.end(), 0, fullArea);
  double result = area / allData.size();
  out << result << "\n";
}

double jirkov::countArea(const Polygon polygon)
{
  int area = 0;
  std::vector< int > areas(polygon.points.size());
  std::vector< int >::iterator startAreas = areas.begin();
  std::vector< int >::iterator finishAreas = areas.end();

  std::vector< Point >::const_iterator finish = polygon.points.end();
  std::vector< Point >::const_iterator prevPoint = polygon.points.begin();
  std::vector< Point >::const_iterator currentPoint = polygon.points.begin() + 1;

  std::transform(currentPoint, finish, prevPoint, startAreas, findCordinate);
  *(finishAreas - 1) = findCordinate(*prevPoint, *(finish - 1));

  area = std::accumulate(startAreas, finishAreas, 0);
  return std::abs(area / 2.0);
}

double jirkov::fullArea(double sum, const Polygon polygon)
{
  sum += countArea(polygon);
  return sum;
}

unsigned long long jirkov::getVertex(const Polygon& polygon)
{
  return polygon.points.size();
}

void jirkov::getMaxVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long maxVertexes = 0;
  if(allData.empty())
  {
    throw std::out_of_range("");
  }
  else
  {
    std::vector< unsigned long long > allVertexes;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertex);
    std::sort(allVertexes.begin(), allVertexes.end());
    maxVertexes = *(allVertexes.end() - 1);
    out << maxVertexes << "\n";
 }
}

void jirkov::getMinVertexes(const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long minVertexes = 0;
  if(allData.empty())
  {
    out << minVertexes << "\n";
  }
  else
  {
    std::vector< unsigned long long > allVertexes;
    std::transform(allData.begin(), allData.end(), std::back_inserter(allVertexes), getVertex);
    std::sort(allVertexes.begin(), allVertexes.end());
    minVertexes = *(allVertexes.begin());
    out << minVertexes << "\n";
  }
}

void jirkov::count(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << std::fixed << std::setprecision(1);
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > count;
  {
    using namespace std::placeholders;
    count["EVEN"] = std::bind(jirkov::countEven, _1, _2);
    count["ODD"] = std::bind(jirkov::countOdd, _1, _2);
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
      countVertex(num, allData, out);
    }
    else
    {
      throw;
    }
  }
}

bool jirkov::findEqual(const Point & point, const Polygon & polygon)
{
  auto numOfPerms = std::count_if(
    polygon.points.begin(),
    polygon.points.end(),
    [point](const Point & compPoint)
    {
      return (compPoint.x == point.x && compPoint.y == point.y) or (compPoint.y == point.x && compPoint.x == point.y);
    }
  );
  return (numOfPerms >= 1);
}

void jirkov::countEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), findEven);
  unsigned long long count = even.size();
  out << count << "\n";
}

void jirkov::countOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), findOdd);
  unsigned long long count = odd.size();
  out << count << "\n";
}
void jirkov::countVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  unsigned long long count = 0;
  std::vector< Polygon > withThisVertexes;
  using namespace std::placeholders;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(withThisVertexes), std::bind(findVertex, num, _1));
  count = withThisVertexes.size();
  out << count << "\n";
}
