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

void kovshikov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  std::map< std::string, std::function < void(const std::vector< Polygon >&, std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(kovshikov::getAreaEven, _1, _2);
   // area["ODD"] = std::bind(kovshikov::getOdd, allData, _1);
   // area["MEAN"] = std::bind(kovshikov::getMean, allData, _1);
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

int kovshikov::getCordMethod(const Point& currentPoint,const Point& prevPoint)
{
  int currentX = currentPoint.x;
  int currentY = currentPoint.y;
  int prevX = prevPoint.x;
  int prevY = prevPoint.y;
  std::cout << "currentX " << currentX << "\n";
  std::cout << "currentY " << currentY << "\n";
  std::cout << "prevX " << prevX << "\n";
  std::cout << "prevY " << prevY << "\n";
  int area = (prevX + currentX) * (prevY - currentY);
  std::cout << area << "\n";
  return area;
}

double kovshikov::countArea(const Polygon polygon) // для одной фигуры
{
  int area = 0;
  std::cout << polygon.points.size() << "\n";
  std::vector< int > areas(polygon.points.size());
  std::vector< int >::iterator startAreas = areas.begin();
  std::vector< int >::iterator finishAreas = areas.end();

  std::vector< Point >::const_iterator finish = polygon.points.end();
  std::vector< Point >::const_iterator prevPoint = polygon.points.begin();
  std::vector< Point >::const_iterator currentPoint = polygon.points.begin() + 1;

  std::cout << *prevPoint << "\n"; //
  std::cout << *currentPoint << "\n"; //
  std::cout << *(finish - 1) << "\n"; //

  std::transform(currentPoint, finish, prevPoint, startAreas, getCordMethod);
  *(finishAreas - 1) = getCordMethod(*prevPoint, *(finish - 1));
  std::cout << getCordMethod(*prevPoint, *(finish - 1)) << "[][][]" << *(finishAreas - 1) << "\n";
 // areas.push_back(getCordMethod(*prevPoint, *(finish - 1)));

  while(startAreas != finishAreas)
  {
    std::cout << *startAreas << "\n"; //
    area += *(startAreas++);
    std::cout << area << "\n"; //
  }
  //area = std::accumulate(startAreas, finishAreas, 0);
  std::cout << "area: " << area << "\n"; //
  return std::abs(area / 2.0);
}

void kovshikov::getAreaEven(const std::vector< Polygon >& allData, std::ostream& out)
{
  double area = countArea(allData.front());
  out << area << "\n";
}

/*void kovshikov::getOdd(std::ostream& out)
{
  out << "getOdd" << "\n";
}


void kovshikov::getMean(std::ostream& out)
{
  out << "getMean" << "\n";
}
*/
void kovshikov::getVertex(std::ostream& out)
{
  out << "getVertex" << "\n";
}

