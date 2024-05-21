#include <iostream>
#include <fstream>
#include <functional>
#include <limits>

#include "commands.hpp"
#include "details.hpp"

int main()
{
  std::cout << "To see all available commands, enter 'help'\n";
  mihalchenko::mapOfDicts_t mapOfDictionaries;
  std::map<std::string, std::function<void(mihalchenko::mapOfDicts_t &, std::istream &, std::ostream &)>>
      cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(mihalchenko::help, _3);
    cmds["open"] = std::bind(mihalchenko::open, _1, _2);
    cmds["save"] = std::bind(mihalchenko::save, _1, _2);
  }
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(mapOfDictionaries, std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID ARGUMENT>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
