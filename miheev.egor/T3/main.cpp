#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include "geometry.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  if (argc > 2)
  {
    std::cerr << "Too many parameters\n";
    return 2;
  }
  else if (argc < 2)
  {
    std::cout << "No input file specified\n";
    return 2;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Error while opening your file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  while (!in.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  areaCommand(std::cin, std::cout, polygons);

  return 0;
}

