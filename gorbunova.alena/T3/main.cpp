#include <iostream>
#include "polygon.hpp"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Error: No input file provided." << std::endl;
    return 1;
  }
  std::string filename = argv[1];
  std::vector< gorbunova::Polygon > polygons = gorbunova::readPolygonsFromFile(filename);
  std::string command;
  while (std::getline(std::cin, command))
  {
    gorbunova::processCommand(command, polygons);
  }
  return 0;
}
