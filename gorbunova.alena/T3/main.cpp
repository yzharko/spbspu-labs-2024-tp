#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <utility>
#include <limits>
#include <functional>
#include <iterator>
#include "commands.hpp"

int main(int argc, char *argv[])
{
  using namespace gorbunova;

  if (argc != 2)
  {
    std::cerr << "Wrong input data\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  std::ifstream input(argv[1]);
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >{input},
      std::istream_iterator< Polygon >{},
      std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< void(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(gorbunova::cmdArea, _1, _2, _3);
    cmds["MAX"] = std::bind(gorbunova::cmdMax, _1, _2, _3);
    cmds["MIN"] = std::bind(gorbunova::cmdMin, _1, _2, _3);
    cmds["COUNT"] = std::bind(gorbunova::cmdCount, _1, _2, _3);
    cmds["PERMS"] = std::bind(gorbunova::cmdPerms, _1, _2, _3);
    cmds["INFRAME"] = std::bind(gorbunova::cmdInframe, _1, _2, _3);
  }

  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(polygons, std::cout, std::cin);
    }
    catch (const std::out_of_range &e)
    {
      outInvalid(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
