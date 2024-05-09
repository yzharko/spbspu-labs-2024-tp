#include <numeric>
#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "polygons.hpp"
#include "commands.hpp"
#include <iomanip>

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
    size_t size = command.length();
    bool isDigit = true;
    for(size_t i = 0; i < size; i++)  //переписать через библиотеку
    {
      if(!std::isdigit(command[i]))
      {
        isDigit = false;
      }
    }
    if(isDigit == true)
    {
      unsigned long long num = std::stoll(command);
      getAreaVertex(num, allData, out);
    }
    else
    {
      std::cerr << "INVALID COMMAND" << "\n";
      is.clear();
      is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
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

double kovshikov::countArea(const Polygon polygon) // для одной фигуры
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

double kovshikov::resultArea(double summa, const Polygon polygon) //для накапливания суммы
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

double kovshikov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > even;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(even), isEven);
  double area = std::accumulate(even.begin(), even.end(), 0, resultArea);
  out << "even area " << area << "\n"; //
  return area;
}

double kovshikov::getAreaOdd(const std::vector< Polygon >& allData, std::ostream& out)
{
  std::vector< Polygon > odd;
  std::copy_if(allData.begin(), allData.end(), std::back_inserter(odd), isOdd);
  double area = std::accumulate(odd.begin(), odd.end(), 0, resultArea);
  out << "odd area " << area << "\n"; //
  return area;
}

double kovshikov::getAreaMean(const std::vector< Polygon >& allData, std::ostream& out)
{
  double area = std::accumulate(allData.begin(), allData.end(), 0, resultArea);
  double result = area / allData.size();
  out << "mean area " << result << "\n"; //
  return result;
}

bool kovshikov::isThisVertex(unsigned long long num, Polygon polygon)
{
  return polygon.points.size() == num;
}

double kovshikov::getAreaVertex(unsigned long long num, const std::vector< Polygon >& allData, std::ostream& out)
{
  using namespace std::placeholders;
  std::vector< Polygon >::const_iterator detected = std::find_if(allData.begin(), allData.end(), std::bind(isThisVertex, num, _1));
  double result = countArea(*detected);
  out << "vertex " << num << "area " << result << "\n";
  return result;
}
