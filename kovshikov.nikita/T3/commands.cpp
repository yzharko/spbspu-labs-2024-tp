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

double kovshikov::countArea(const Polygon polygon) // для одной фигуры
{
  double area = 0.0;
  std::vector< Point >::const_iterator start = polygon.points.begin();
  std::vector< Point >::const_iterator finish = polygon.points.end();
  std::vector< Point >::const_iterator temp = finish - 1;
  while(start != finish)
  {
    double x1 = static_cast< double >(start->x);
    double y1 = static_cast< double >(start->y);
    double x2 = static_cast< double >(temp->x);
    double y2 = static_cast< double >(temp->y);
    temp = start;
    start++;
    area += (x2 + x1) * (y2 - y1);
  }
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

