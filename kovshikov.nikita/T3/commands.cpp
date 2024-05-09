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
/*
void kovshikov::getArea(const std::vector< Polygon >& allData, std::istream& is, std::ostream& out)
{
  out << "getArea" << "\n";
}
*/

void kovshikov::getArea(std::istream& is, std::ostream& out)
{
  std::map< std::string, std::function < void(std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(kovshikov::getEven, _1);
    area["ODD"] = std::bind(kovshikov::getOdd, _1);
    area["MEAN"] = std::bind(kovshikov::getMean, _1);
  }
  out << "getArea" << "\n";
  std::string command;
  is >> command;
  try
  {
    area.at(command)(out);
  }
  catch(const std::out_of_range& error)
  {
    std::cerr << "INVALID COMMAND" << "\n";
    is.clear();
    is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}


void kovshikov::getEven(std::ostream& out)
{
  out << "getEven" << "\n";
}


void kovshikov::getOdd(std::ostream& out)
{
  out << "getOdd" << "\n";
}


void kovshikov::getMean(std::ostream& out)
{
  out << "getMean" << "\n";
}