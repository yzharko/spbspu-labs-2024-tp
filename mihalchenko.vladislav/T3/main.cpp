#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>
#include "functions.hpp"
#include "figures.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Not enough input parameters...";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "The file cannot be opened\n";
    return 2;
  }
  using namespace mihalchenko;
  std::vector<Polygon> polygons;
  while (!inputFile.eof())
  {
    std::copy(std::istream_iterator<Polygon>(inputFile),
      std::istream_iterator<Polygon>(),
      std::back_inserter(polygons));
    if (inputFile.fail())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function<void(const std::vector<Polygon> &polygon,
                                           std::istream &is, std::ostream &out)>> cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(printArea, _1, _2, _3);
    cmds["MAX"] = std::bind(printMax, _1, _2, _3);
    cmds["MIN"] = std::bind(printMin, _1, _2, _3);
    cmds["COUNT"] = std::bind(printCount, _1, _2, _3);
    cmds["PERMS"] = std::bind(printPerms, _1, _2, _3);
    cmds["RIGHTSHAPES"] = std::bind(printCountRightShapes, _1, _2, _3);
  }
  mihalchenko::Polygon polygon;
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(polygons, std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      printErrorMessage("<INVALID COMMAND>", std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
