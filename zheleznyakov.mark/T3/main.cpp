#include <iostream>
#include <fstream>
#include <map>
#include <functional>
#include <limits>
#include <iterator>
#include "geometry.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace zheleznyakov;
  using std::istream;
  using std::ostream;

  if (argc != 2)
  {
    std::cerr << "Wrong arguments count\n";
    return 2;
  }

  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "Unable to read file\n";
    return 2;
  }

  std::vector< Polygon > polygons;
  while (!in.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(in),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (in.fail() && !in.eof())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function< ostream &(const std::vector< Polygon > &, istream &, ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(commands::area, _1, _2, _3);
    cmds["MAX"] = std::bind(commands::max, _1, _2, _3);
    cmds["MIN"] = std::bind(commands::min, _1, _2, _3);
    cmds["COUNT"] = std::bind(commands::count, _1, _2, _3);
    cmds["MAXSEQ"] = std::bind(commands::maxseq, _1, _2, _3);
    cmds["SAME"] = std::bind(commands::same, _1, _2, _3);
  }

  std::string currentCommand = "";
  while (std::cin >> currentCommand)
  {
    try
    {
      cmds.at(currentCommand)(polygons, std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      outInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
