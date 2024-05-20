#include <iostream>
#include <limits>
#include "commands.hpp"

int main()
{
  using std::istream;
  using std::ostream;

  zheleznyakov::strings_t strings;

  std::map< std::string, std::function< ostream &(zheleznyakov::strings_t &, istream &, ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(zheleznyakov::commands::help, _2, _3);
  }

  std::string currentCommand = "";
  while (std::cin >> currentCommand)
  {
    try
    {
      cmds.at(currentCommand)(strings, std::cin, std::cout);
    }
    catch (const std::exception &e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
