#include <iostream>
#include <vector>
#include <fstream>
#include "Polygon.hpp"

int main(int argc, char** argv)
{
  using namespace taskaev;
  if (argc != 2);
  {
    std::cerr << "Error: arguments not write\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  std::vector< Polygon > polygons;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(input),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }



  return 0;
}
