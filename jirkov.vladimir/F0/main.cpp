#include <functional>
#include <limits>
#include <iostream>
#include "commands.hpp"
//
int main()
{
  using dictionary = std::multimap< std::string, std::string >;
  std::map< std::string, dictionary > dicts;
  std::map< std::string, std::function< void(std::map< std::string, dictionary >&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["help"] = std::bind(jirkov::help, _2, _3);
    commands["create"] = std::bind(jirkov::createDict, _1, _2, _3);
    commands["remove"] = std::bind(jirkov::removeDict, _1, _2, _3);
    commands["print"] = std::bind(jirkov::printDict, _1, _2, _3);
    commands["sort"] = std::bind(jirkov::sortDict, _1, _2, _3);
    commands["delete"] = std::bind(jirkov::deleteFile, _1, _2, _3);
    commands["find"] = std::bind(jirkov::findFile, _1, _2, _3);
  }
  while (std::cin >> cmd && cmd != "save")
  {
    try
    {
      commands.at(cmd)(dicts, std::cin, std::cout);
    }
    catch (const std::invalid_argument& e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::out_of_range& e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
