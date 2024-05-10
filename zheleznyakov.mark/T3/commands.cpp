#include "commands.hpp"

std::ostream & zheleznyakov::commands::area(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string r;
  in >> r;
  out << "Got argument: " << r << "\n";
  return out << polygons.size();
}
