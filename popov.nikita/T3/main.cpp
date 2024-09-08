#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include <limits>
#include <functional>
#include "commands.hpp"
#include "polygon.hpp"

int main(int argc, char* argv[])
{
  using namespace popov;
  if (argc != 2)
  {
    std::cerr << "not enough arguments" << "\n";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  std::vector< Polygon > polygons;
  while (!inputFile.eof())
  {
    std::copy
    (
      std::istream_iterator< Polygon >(inputFile),
      std::istream_iterator< Polygon >(),
      std::back_inserter(polygons)
    );
    if (inputFile.fail())
    {
    inputFile.clear();
    inputFile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::map< std::string, std::function< void(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)> > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(getArea, _1, _2, _3);
    cmds["MAX"] = std::bind(maxCount, _1, _2, _3);
    cmds["MIN"] = std::bind(minCount, _1, _2, _3);
    cmds["COUNT"] = std::bind(count, _1, _2, _3);
    cmds["INFRAME"] = std::bind(inframe, _1, _2, _3);
    cmds["MAXSEQ"] = std::bind(maxSeq, _1, _2, _3);
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(polygons, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      invalidMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
