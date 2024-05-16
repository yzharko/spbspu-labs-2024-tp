#include <iostream>
#include <functional>
#include "menu.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using mapDictionaries_t = std::map< std::string, std::map< std::string, size_t > >;

  mapDictionaries_t mapDictionaries;
  nikiforov::ActionsOnTheDictionary A;

  std::map< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&) > > command;
  {
    command["help"] = std::bind(nikiforov::printCommands);
    command["create"] = nikiforov::createDictionary;
    command["delete"] = nikiforov::deleteDictionary;
    command["list"] = nikiforov::printNamesDictionaries;
    command["add"] = nikiforov::add;
    command["unite"] = nikiforov::unite;
    command["rename"] = nikiforov::rename;
    command["clear"] = nikiforov::clear;

    using namespace nikiforov;
    using namespace std::placeholders;
    command["select"] = std::bind(&ActionsOnTheDictionary::select, &A, _1, _2, _3);
    command["print"] = std::bind(&ActionsOnTheDictionary::print, &A, _1, _2, _3);
  }

  std::string cmd = "";

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
