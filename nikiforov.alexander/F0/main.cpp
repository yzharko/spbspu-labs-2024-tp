#include <iostream>
#include <functional>
#include "menu.hpp"
#include "commands.hpp"

int main()
{
  using mapDictionaries_t = std::map< std::string, std::map< std::string, size_t > >;

  mapDictionaries_t mapDictionaries;
  nikiforov::ActionsOnTheDictionary A;

  using namespace std::placeholders;
  std::map< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&) > > command;
  {
    command["help"] = std::bind(nikiforov::printCommands);
    command["create"] = std::bind(nikiforov::createDictionary, _1, _2, "");
    command["open"] = nikiforov::open;
    command["delete"] = nikiforov::deleteDictionary;
    command["list"] = std::bind(nikiforov::printNamesDictionaries, _1, _3);
    command["add"] = nikiforov::add;
    command["unite"] = nikiforov::unite;
    command["rename"] = nikiforov::rename;
    command["clear"] = nikiforov::clear;
    command["save"] = nikiforov::save;

    using namespace nikiforov;
    command["select"] = std::bind(&ActionsOnTheDictionary::select, &A, _1, _2, _3);
    command["print"] = std::bind(&ActionsOnTheDictionary::print, &A, _1, _2, _3);
    command["find"] = std::bind(&ActionsOnTheDictionary::find, &A, _1, _2, _3);
    command["erase"] = std::bind(&ActionsOnTheDictionary::erase, &A, _1, _2, _3);
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
