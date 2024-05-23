#include <iostream>
#include <functional>
#include "menu.hpp"
#include "commands.hpp"

int main()
{
  using mapDictionaries_t = std::map< std::string, std::map< std::string, size_t > >;

  mapDictionaries_t mapDictionaries;
  nikiforov::ActionsOnTheDictionary SelectedDictionary;

  using namespace std::placeholders;
  std::map< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&) > > command;
  {
    command["help"] = std::bind(nikiforov::printCommands);
    command["create"] = std::bind(nikiforov::createDictionary, _1, _2, _3, "");
    command["open"] = nikiforov::open;
    command["delete"] = nikiforov::deleteDictionary;
    command["list"] = std::bind(nikiforov::printNamesDictionaries, _1, _3);
    command["add"] = nikiforov::add;
    command["unite"] = nikiforov::unite;
    command["rename"] = nikiforov::rename;
    command["clear"] = nikiforov::clear;
    command["save"] = nikiforov::save;
    command["select"] = std::bind(&nikiforov::ActionsOnTheDictionary::select, &SelectedDictionary, _1, _2, _3);
    command["print"] = std::bind(&nikiforov::ActionsOnTheDictionary::print, &SelectedDictionary, _1, _2, _3);
    command["find"] = std::bind(&nikiforov::ActionsOnTheDictionary::find, &SelectedDictionary, _1, _2, _3);
    command["erase"] = std::bind(&nikiforov::ActionsOnTheDictionary::erase, &SelectedDictionary, _1, _2, _3);
  }

  std::string cmd = "";

  std::cout << "Enter any valid command (the 'help' command to output all available commands)\n";
  while (std::cin >> cmd)
  {
    try
    {
      command.at(cmd)(mapDictionaries, std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}
