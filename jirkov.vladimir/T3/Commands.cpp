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
  out << "getArea" << "\n";
}

void jirkov::getArea(std::istream& is, std::ostream& out)
{
  std::map< std::string, std::function < void(std::ostream&) > > area;
  {
    using namespace std::placeholders;
    area["EVEN"] = std::bind(jirkov::getEven, _1);
    area["ODD"] = std::bind(jirkov::getOdd, _1);
    area["MEAN"] = std::bind(jirikov::getMean, _1);
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

void kovshikov::getVertex(std::ostream& out)
{
  out << "getVertex" << "\n";
}
