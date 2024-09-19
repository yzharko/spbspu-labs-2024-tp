#include <iostream>
#include <fstream>
#include <functional>
#include "Commands.h"
#include <map>

int main(int argc, char** argv) {
  using namespace batunov;
  std::vector < Polygon > polygons;
  if (argc < 2)
  {
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    return 1;
  }
  std::map < std::string, std::function <
  void (std::istream &, std::ostream &, std::vector < Polygon > &)>> command;
  command["AREA"] = area;
  command["MAX"] = max;
  command["MIN"] = min;
  command["COUNT"] = count;
  command["PERMS"] = perms;
  command["INFRAME"] = inframe;
  while (!input.eof())
  {
    std::copy(
        std::istream_iterator< Polygon >(input),
        std::istream_iterator< Polygon >(),
        std::back_inserter(polygons)
    );
    if (input.fail() && !input.eof())
    {
      input.clear();
    }
  }

  std::string cmd;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
    }
    try
    {
      std::cin >> cmd;
      if (std::cin.eof())
      {
        break;
      }
      auto func = command.find(cmd);
      if (func == command.end()) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("");
      }
      func->second(std::cin, std::cout, polygons);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }

  return 0;
}
