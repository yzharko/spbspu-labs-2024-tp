#include <iostream>
#include <limits>
#include "commands.hpp"

int main()
{
  using namespace maksimov;
  using std::istream;
  using std::ostream;

  std::string activeString = "";
  strings_t strings;

  std::map< std::string, std::function< ostream &(strings_t &, std::string &, istream &, ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(commands::help, _3, _4);
    cmds["list"] = std::bind(commands::list, _1, _3, _4);
    cmds["rm"] = std::bind(commands::rm, _1, _3, _4);
    cmds["create"] = std::bind(commands::create, _1, _3, _4);
    cmds["cmp"] = std::bind(commands::cmp, _1, _3, _4);
    cmds["diff"] = std::bind(commands::diff, _1, _3, _4);
    cmds["enter"] = std::bind(commands::enter, _1, _2, _3, _4);

    cmds["read"] = std::bind(commands::read, _1, _2, _3, _4);
    cmds["table"] = std::bind(commands::table, _1, _2, _3, _4);
    cmds["info"] = std::bind(commands::info, _1, _2, _3, _4);
    cmds["stats"] = std::bind(commands::stats, _1, _2, _3, _4);
    cmds["quit"] = std::bind(commands::quit, _2, _3, _4);
  }

  std::cout << prompt(activeString);
  std::string currentCommand = "";
  while (std::cin >> currentCommand)
  {
    try
    {
      if (cmds.find(currentCommand) == cmds.end())
      {
        throw std::logic_error(statusString("Command not found\n", "error"));
      }
      cmds.at(currentCommand)(strings, activeString, std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cout << prompt(activeString);
  }
  return 0;
}
