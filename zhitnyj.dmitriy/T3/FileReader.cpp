#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include "iofmtguard.hpp"
#include "FileReader.hpp"

struct DelimiterIO
{
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) return in;
  char c;
  in >> c;
  if (in && c != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::vector< Polygon > FileReader::readPolygons(const std::string& filename) const
{
  std::vector< Polygon > polygons;
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("Unable to open file");
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    int vertex_count;
    if (!(iss >> vertex_count))
    {
      continue;
    }
    Polygon polygon;
    std::generate_n(std::back_inserter(polygon.points), vertex_count, [&iss]()
    {
      Point point;
      iss >> DelimiterIO{ '(' } >> point.x >> DelimiterIO{ ';' } >> point.y >> DelimiterIO{ ')' };
      return point;
    });
    if (polygon.points.size() == static_cast<std::vector<Point>::size_type>(vertex_count))
    {
        polygons.push_back(polygon);
    }
  }
  return polygons;
}
