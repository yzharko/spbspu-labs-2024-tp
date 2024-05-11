#include <fstream>
#include <iostream>
#include <map>
#include <functional>
#include <limits>
#include <iterator>
#include "commands.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: can't open file";
    return 2;
  }

  std::vector< ponomarev::Polygon > data;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< ponomarev::Polygon >(input),
      std::istream_iterator< ponomarev::Polygon >(),
      std::back_inserter(data)
    );
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map<
    std::string,
    std::function< std::ostream & (std::istream &, std::ostream &, const std::vector< ponomarev::Polygon > &) >
  > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(ponomarev::chooseAreaCommand, _1, _2, _3);
    commands["MAX"] = std::bind(ponomarev::getMax, _1, _2, _3);
    commands["MIN"] = std::bind(ponomarev::getMin, _1, _2, _3);
    commands["COUNT"] = std::bind(ponomarev::count, _1, _2, _3);
    commands["RECTS"] = std::bind(ponomarev::countRects, _1, _2, _3);
    commands["INTERSECTIONS"] = std::bind(ponomarev::countIntersections, _1, _2, _3);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, data);
    }
    catch (const std::logic_error&)
    {
      ponomarev::printMessage(std::cout, "<INVALID COMMAND>");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
