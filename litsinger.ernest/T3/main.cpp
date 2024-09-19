#include <iostream>
#include <map>
#include <iostream>
#include <vector>
#include <functional>
#include <limits>
#include <fstream>
#include "FigureStructs.hpp"
#include "Commands.hpp"
#include "InputProcessing.hpp"

int main(int argc, const char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "wrong number of args\n";
    return 1;
  }
  std::vector< litsinger::Polygon > inputData;
  std::ifstream input(argv[1]);
  litsinger::readFromFile(input, inputData);
  std::map< std::string, std::function< void(const std::vector< litsinger::Polygon >&, std::ostream&, std::istream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(litsinger::areaCommand, _1, _2, _3);
    commands["MAX"] = std::bind(litsinger::maxCommand, _1, _2, _3);
    commands["MIN"] = std::bind(litsinger::minCommand, _1, _2, _3);
    commands["COUNT"] = std::bind(litsinger::countCommand, _1, _2, _3);
    commands["PERMS"] = std::bind(litsinger::permsCommand, _1, _2, _3);
    commands["RECTS"] = std::bind(litsinger::rectsCommand, _1, _2);
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(inputData, std::cout, std::cin);
    }
    catch (const std::exception & e)
    {
      litsinger::getOutputMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
