#include <iostream>
#include <functional>
#include "menu.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  std::map< std::string, std::map< std::string, size_t > > mapDictionaries;

  using namespace std::placeholders;
  std::map< std::string, std::function < void(std::map< std::string, std::map< std::string, size_t > >& , std::istream&, std::ostream&) > > command;
  {
    command["help"] = std::bind(nikiforov::printCommands);
    command["create"] = nikiforov::createDictionary, mapDictionaries, _1, _2;
    command["delete"] = nikiforov::deleteDictionary, mapDictionaries, _1, _2;
    command["list"] = nikiforov::printNamesDictionaries, mapDictionaries, _1, _2;
    command["add"] = nikiforov::add, mapDictionaries, _1, _2;
    command["unite"] = nikiforov::unite, mapDictionaries, _1, _2;
    command["rename"] = nikiforov::rename, mapDictionaries, _1, _2;
    command["clear"] = nikiforov::clear, mapDictionaries, _1, _2;
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
