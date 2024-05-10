#include <limits>
#include <iostream>
#include <vector>
#include <functional>
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
  std::map< std::string, std::function< void(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)> > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(AreaComand, _1, _2, _3);
    cmds["MAX"] = std::bind(MaxComand, _1, _2, _3);
    cmds["MIN"] = std::bind(MinComand, _1, _2, _3);
    cmds["COUNT"] = std::bind(CountComand, _1, _2, _3);
    // later
    // MaxSeq
    // Same
  }

  std::string cmd = "";
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(polygons, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
