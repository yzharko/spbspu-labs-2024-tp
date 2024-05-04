#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <functional>
#include <iterator>
#include "commands.hpp"
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
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(std::istream_iterator< sobolevsky::Polygon >(file),
    std::istream_iterator< sobolevsky::Polygon >(), std::back_inserter(polygons));
  }

  std::map< std::string, std::function < void( const std::vector< sobolevsky::Polygon > & vec,
  std::istream & in, std::ostream & out) > > cmds;
  cmds["AREA"] = sobolevsky::area;
  cmds["MAX"] = sobolevsky::getMax;
  cmds["MIN"] = sobolevsky::getMin;
  cmds["COUNT"] = sobolevsky::count;
  cmds["INTERSECTIONS"] = sobolevsky::intersections;
  cmds["SAME"] = sobolevsky::same;
  std::string cmd;
  std::cout << std::fixed;
  std::cout.precision(1);
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(polygons, std::cin, std::cout);
    }
    catch(std::exception&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }
  return 0;
}
