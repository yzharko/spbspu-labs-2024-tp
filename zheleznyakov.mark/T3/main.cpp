#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include <limits>
#include "geometry.hpp"
#include "commands.hpp"

int main()
{
  using namespace zheleznyakov;
  using std::istream;
  using std::ostream;

  std::vector< Polygon > polygons;

  std::map< std::string, std::function< ostream &(const std::vector< Polygon > &, istream &, ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(commands::area, _1, _2, _3);
  }
  
  std::string currentCommand = "";
  while (std::cin >> currentCommand)
  {
    try
    {
      cmds.at(currentCommand)(polygons, std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cerr << "Something went wrong\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max() , '\n');
    }
  }

  return 0;
}
