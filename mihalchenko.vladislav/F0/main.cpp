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
  std::map<std::string, std::function<void(mihalchenko::mapOfDicts_t &,
                                           std::istream &, std::ostream &)>>
      cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(mihalchenko::help, _3);
    cmds["create"] = std::bind(mihalchenko::create, _1, _2);
    cmds["save"] = std::bind(mihalchenko::save, _1, _3);
    cmds["size"] = std::bind(mihalchenko::size, _1, _2, _3);
    cmds["view"] = std::bind(mihalchenko::view, _1, _3);
    cmds["find"] = std::bind(mihalchenko::find, _1, _2, _3);
    cmds["rename"] = std::bind(mihalchenko::rename, _1, _2, _3);
    cmds["delete"] = std::bind(mihalchenko::deleteDict, _1, _2, _3);
    cmds["edit"] = std::bind(mihalchenko::edit, _1, _2, _3);
    cmds["insert"] = std::bind(mihalchenko::insert, _1, _2, _3);
    cmds["remove"] = std::bind(mihalchenko::remove, _1, _2, _3);
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
      mihalchenko::printInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
