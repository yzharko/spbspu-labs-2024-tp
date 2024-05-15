#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <map>
#include "FileReader.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::string filename = argv[1];
  std::vector< Polygon > polygons;

  try
  {
    polygons = FileReader().readPolygons(filename);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error reading file: " << e.what() << "\n";
    return 2;
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&, std::vector< Polygon >&)>> cmds;
  cmds["AREA"] = std::bind(areaCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["MAX"] = std::bind(maxCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["MIN"] = std::bind(minCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["COUNT"] = std::bind(countCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["RMECHO"] = std::bind(rmechoCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  cmds["PERMS"] = std::bind(permsCommand, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      auto it = cmds.find(cmd);
      if (it != cmds.end())
      {
        it->second(std::cin, std::cout, polygons);
      }
      else
      {
        throw std::invalid_argument("Invalid command");
      }
    }
    catch (const std::invalid_argument&)
    {
      printInvalidCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
