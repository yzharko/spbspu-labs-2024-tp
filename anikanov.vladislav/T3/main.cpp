#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>

#include "polygon.hpp"
#include "point.hpp"

int main(int argc, char **argv)
{
  using namespace anikanov;

  if (argc < 2 || argc > 2) {
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input) {
    return 1;
  }

  std::vector< Polygon > polygons;
  Polygon pol;

  while (input >> pol) {
    if (input.eof()) {
      break;
    }
    polygons.push_back(pol);
    std::cout << polygons[polygons.size() - 1].getSize() << '\n';
  }

  return 0;
}
