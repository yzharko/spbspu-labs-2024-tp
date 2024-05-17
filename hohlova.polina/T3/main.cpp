#include "polygon.hpp"
#include "commands.hpp"
#include <iterator>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <limits>

using namespace hohlova;
int main(int argc, char* argv[])
{

  std::ifstream in(argv[1]);
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }
  std::vector< Polygon > polygons;
  while (!in.eof())
  {
    std::copy
    (
      std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max());
    }
  }
  using CommandFunction = std::function< void(const std::vector< Polygon >&, std::istream&, std::ostream&)>;
  std::map< std::string, CommandFunction > command;

  using namespace std::placeholders;
  command["AREA"] = std::bind(AREACommandMenu, _1, _2, _3);
  command["MAX"] = std::bind(MAXCommandMenu, _1, _2, _3);
  command["MIN"] = std::bind(MINCommandMenu, _1, _2, _3);
  command["COUNT"] = std::bind(COUNTCommandMenu, _1, _2, _3);
  command["PERMS"] = std::bind(PERMSCommandMenu, _1, _2, _3);
  command["MAXSEQ"] = std::bind(MAXSEQCommandMenu, _1, _2, _3);
  command["RIGHTSHAPES"] = std::bind(RIGHTSHAPESCommandMenu, _1, _3);

  std::string incommand;
  while (std::cin >> incommand)
  {
    try
    {
      if (polygons.size())
        command.at(incommand)(polygons, std::cin, std::cout);
    }
    catch (std::exception e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
