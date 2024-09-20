#include <iostream>
#include <functional>
#include <limits>
#include "commands.hpp"

int main()
{
  using panov::dicts_t;
  using std::istream;
  using std::ostream;

  dicts_t dicts;

  std::map< std::string, std::function< ostream &(dicts_t &, istream &, ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["help"] = std::bind(panov::help, _2, _3);
    commands["create"] = std::bind(panov::create, _1, _2, _3);
    commands["add"] = std::bind(panov::add, _1, _2, _3);
    commands["delete"] = std::bind(panov::deleteWord, _1, _2, _3);
    commands["change"] = std::bind(panov::change, _1, _2, _3);
    commands["reset"] = std::bind(panov::reset, _1, _2, _3);
    commands["print"] = std::bind(panov::print, _1, _2, _3);
    commands["get"] = std::bind(panov::get, _1, _2, _3);
    commands["intersection"] = std::bind(panov::intersection, _1, _2, _3);
    commands["addLine"] = std::bind(panov::addline, _2, _3);
    commands["search"] = std::bind(panov::search, _1, _2, _3);
  }

  std::string currentCommand = "";
  while (std::cin >> currentCommand)
  {
    try
    {
      if (commands.find(currentCommand) == commands.end())
      {
        std::cout << "Command not found\n";
        throw std::logic_error("");
      }
      commands.at(currentCommand)(dicts, std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
