#include <iostream>
#include <map>
#include <iterator>
#include <fstream>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  /*if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }*/

  //std::ifstream input(argv[1]);
  std::ifstream input;
  input.open("../x64/Debug/input.txt");

  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  std::vector< nikiforov::Polygon > shapes;

  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< nikiforov::Polygon >(input),
      std::istream_iterator< nikiforov::Polygon >(),
      std::back_inserter(shapes)
    );
    if (input.fail() && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using namespace std::placeholders;
  std::map< std::string, std::function < void(std::istream&, std::ostream&) > > cmds;
  {
    cmds["AREA"] = std::bind(nikiforov::takingArea, shapes, _1, _2);
    cmds["MAX"] = std::bind(nikiforov::takingMax, shapes, _1, _2);
    cmds["MIN"] = std::bind(nikiforov::takingMin, shapes, _1, _2);
    cmds["COUNT"] = std::bind(nikiforov::takingCount, shapes, _1, _2);
    cmds["INTERSECTIONS"] = std::bind(nikiforov::takingIntersections, shapes, _1, _2);
    cmds["SAME"] = std::bind(nikiforov::takingSame, shapes, _1, _2);
  }

  std::function < void(std::ostream&) > outError = std::bind(nikiforov::takingError, _1, "<INVALID COMMAND>");

  std::string cmd = "";

  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      outError(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
