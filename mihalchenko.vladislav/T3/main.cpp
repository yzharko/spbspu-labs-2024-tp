#include <iostream>
#include <fstream>
#include <limits>
#include "figures.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Not enough input parameters...";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cout << "The file cannot be opened\n";
    return 2;
  }
  using namespace mihalchenko;
  std::vector<Polygon> polygons;
  while (!inputFile.eof())
  {
    std::copy(std::istream_iterator<Polygon>(inputFile),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));
    if (inputFile.fail())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  while (!std::cin.eof())
  {
    size_t counterOfPointers = 0;
    std::string points = "";
    std::getline(std::cin, points);
  }
}
