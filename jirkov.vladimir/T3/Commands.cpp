#include <numeric>
#include <cstring>
#include <map>
#include <functional>
#include <fstream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "geoStructures.hpp"
#include "Commands.hpp"

void jirkov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(jirkov::getAreaEven, _1, _2);
  }
  out << "getArea" << "\n";
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
    for(size_t i = 0; i < size; i++)
    {
      if(!std::isdigit(command[i]))
      {
        isDigit = false;
      }
    }
    if(isDigit == true)
    {
      std::cout << std::stoll(command);
      getVertex(out);
    }
    else
    {
      std::cerr << "INVALID COMMAND" << "\n";
      is.clear();
      is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
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

void jirkov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  double area = countArea(allData.front());
  out << area << "\n";
}
void jirkov::getVertex(std::ostream& out)
{
  out << "getVertex" << "\n";
}
