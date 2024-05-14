#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "FileReader.hpp"
#include "Polygon.hpp"

std::vector< Polygon > FileReader::readPolygons(const std::string& filename) const
{
  std::vector< Polygon > polygons;
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Unable to open file");
  }

  while (!file.eof())
  {
    Polygon polygon;
    file >> polygon;
    if (!file.fail())
    {
      polygons.push_back(polygon);
    }
    else
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return polygons;
}
