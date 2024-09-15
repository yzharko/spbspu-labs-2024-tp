#include <iostream>
#include <map>
#include "fstream"
#include <functional>
#include <limits>
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace jirkov;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  using input_iterator_t = std::istream_iterator< Polygon >;
  std::ifstream in(argv[1]);
  std::vector< Polygon > polygons;
  while (!in.eof())
  {
    std::copy(input_iterator_t{in}, input_iterator_t{}, std::back_inserter(polygons));
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
