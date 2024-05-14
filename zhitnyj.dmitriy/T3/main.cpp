#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <functional>
#include <map>
#include "FileReader.hpp"
#include "Commands.hpp"
#include "iofmtguard.hpp"

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

  Commands commands(polygons);

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  cmds["AREA"] = std::bind(&Commands::areaCommand, &commands, std::placeholders::_1, std::placeholders::_2);
  cmds["MAX"] = std::bind(&Commands::maxCommand, &commands, std::placeholders::_1, std::placeholders::_2);
  cmds["MIN"] = std::bind(&Commands::minCommand, &commands, std::placeholders::_1, std::placeholders::_2);
  cmds["COUNT"] = std::bind(&Commands::countCommand, &commands, std::placeholders::_1, std::placeholders::_2);
  cmds["RMECHO"] = std::bind(&Commands::rmechoCommand, &commands, std::placeholders::_1, std::placeholders::_2);
  cmds["PERMS"] = std::bind(&Commands::permsCommand, &commands, std::placeholders::_1, std::placeholders::_2);

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      auto it = cmds.find(cmd);
      if (it != cmds.end())
      {
        it->second(std::cin, std::cout);
      }
      else
      {
        throw std::invalid_argument("Invalid command");
      }
    }
    catch (const std::invalid_argument&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
