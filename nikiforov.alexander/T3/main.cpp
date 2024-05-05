#include <iostream>
#include <map>
#include <iterator>
#include <fstream>
#include "commands.hpp"

int main(int argc, char* argv[])
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

  std::vector< nikiforov::Polygon > figure;

  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< nikiforov::Polygon >(input),
      std::istream_iterator< nikiforov::Polygon >(),
      std::back_inserter(figure)
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
    cmds["AREA"] = std::bind(nikiforov::takingArea, figure, _1, _2);
    cmds["MAX"] = std::bind(nikiforov::takingMax, figure, _1, _2);
    cmds["MIN"] = std::bind(nikiforov::takingMin, figure, _1, _2);
    cmds["COUNT"] = std::bind(nikiforov::takingCount, figure, _1, _2);
  }

  std::string cmd = "";

  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
