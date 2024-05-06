#include <map>
#include <functional>
#include <limits>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }
  std::ifstream input(argv[1]);

  std::vector< psarev::Polygon > polyVec;

  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< psarev::Polygon >(input),
      std::istream_iterator< psarev::Polygon >(),
      std::back_inserter(polyVec)
    );
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < std::ostream& (std::vector < psarev::Polygon >&, std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(psarev::chooseAreaType, _1, _2, _3);
    cmds["MAX"] = std::bind(psarev::chooseMaxOpt, _1, _2, _3);
    cmds["MIN"] = std::bind(psarev::chooseMinOpt, _1, _2, _3);
    cmds["COUNT"] = std::bind(psarev::chooseCountOpt, _1, _2, _3);
    cmds["RECTS"] = std::bind(psarev::countRects, _1, _2, _3);
    cmds["INFRAME"] = std::bind(psarev::checkInframe, _1, _2, _3);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(polyVec, std::cin, std::cout);
    }
    catch (const std::logic_error&)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
