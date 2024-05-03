#include <iostream>
#include <map>
#include "commands.hpp"

int main(int argc, char* argv[])
{
  std::ifstream input(argv[1]);
  //std::ifstream input;
  //input.open("../x64/Debug/input.txt");
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
    catch (const std::overflow_error& e)
    {
      std::cerr << "<GOTH_ERROR: " << e.what() << ">\n";
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
