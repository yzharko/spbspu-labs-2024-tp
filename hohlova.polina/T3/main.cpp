#include "polygon.hpp"
#include "commands.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }
  std::vector<Polygon> polygons = hohlova::readPolygonsFromFile(argv[1]);
  if (polygons.empty())
  {
    std::cerr << "No valid polygons found in the file.\n";
    return 1;
  }
  hohlova::processCommands(polygons);
  return 0;
}
