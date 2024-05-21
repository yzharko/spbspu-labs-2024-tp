#include <iostream>
#include <iomanip>
#include <limits>
#include <map>

#include "polygon.hpp"
#include "mainExtensions.hpp"

int main(int argc, char **argv)
{
  using namespace anikanov;

  if (argc < 2 || argc > 2) {
    return 1;
  }

  std::string filename = argv[1];
  std::vector< Polygon > polygons;

  try {
    polygons = readPolygons(filename);
  }
  catch (const std::exception &e) {
    std::cerr << "Error reading file: " << e.what() << "\n";
    return 2;
  }

  std::map< std::string, std::function< void(std::vector< Polygon > &, std::istream &, std::ostream &)>> cmds;
  cmds["AREA"] = std::bind(area, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["MAX"] = std::bind(anikanov::max, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["MIN"] = std::bind(anikanov::max, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["COUNT"] = std::bind(count, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["RECTS"] = std::bind(rects, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["RIGHTSHAPES"] = std::bind(rightShapes, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  std::string cmd;
  while (std::cin >> cmd) {
    try {
      auto it = cmds.find(cmd);
      if (it != cmds.end()) {
        it->second(polygons, std::cin, std::cout);
      } else {
        throw std::runtime_error("Invalid command");
      }
    } catch (const std::runtime_error &er) {
      printErrorMessage(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    cmd.clear();
  }

  return 0;
}
