#include <map>
#include <functional>
#include <limits>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  /*std::ifstream input(argv[1]);*/
  std::ifstream input;
  input.open("./x64/Debug/inputT2.txt");

  std::vector< psarev::Polygon > polyVec;

  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< psarev::Polygon >(input),
      std::istream_iterator< psarev::Polygon >(),
      std::back_inserter(polyVec)
    );
    if (input.fail() && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  int context = 0;

  std::map< std::string, std::function < void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(psarev::areaOdd, polyVec[0], _1, _2, _3);
    //cmds["AREA2"] = std::bind(psarev::areaEven, context, _1, _2);
    //cmds["AREA3"] = std::bind(psarev::areaMean, context, _1, _2);
    //cmds["AREA4"] = std::bind(psarev::areaNumOfVerts, context, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}