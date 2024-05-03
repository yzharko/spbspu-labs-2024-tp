#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <functional>
#include <iterator>
#include "point.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "missed filename\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "file cannot be opened\n";
    return 1;
  }

  std::vector< sobolevsky::Polygon > polygons;
  while (!file.eof())
  {
    std::cout << "test\n";
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< sobolevsky::Polygon >(file), std::istream_iterator< sobolevsky::Polygon >(), std::back_inserter(polygons));
  }

  std::cout << polygons.size() << "\n";
}
