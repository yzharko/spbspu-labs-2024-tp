#include <fstream>
#include <iostream>
#include <map>
#include <functional>
#include <limits>
#include <iterator>
#include "polygon.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  std::vector< ponomarev::Polygon > data;
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< ponomarev::Polygon >(input),
      std::istream_iterator< ponomarev::Polygon >(),
      std::back_inserter(data)
    );
    if (input.fail() && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
