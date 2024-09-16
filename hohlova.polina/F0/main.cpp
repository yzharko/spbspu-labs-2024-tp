#include <iostream>
#include <unordered_map>
#include "commands.hpp"
#include <functional>
#include <locale>
#include <limits>

std::unordered_map< std::string, std::function< void(hohlova::DictOfDictionary&, std::istream&, std::ostream&) > > commands;

int main()
{
  using namespace std::placeholders;
  setlocale(LC_ALL, "Russian");

  commands["help"] = std::bind(hohlova::help, _3);
  commands["create"] = std::bind(hohlova::create, _1, _2);
  commands["size"] = std::bind(hohlova::size, _1, _2, _3);
  commands["view"] = std::bind(hohlova::view, _1, _3);
  commands["find"] = std::bind(hohlova::find, _1, _2, _3);
  commands["rename"] = std::bind(hohlova::rename, _1, _2, _3);
  commands["edit"] = std::bind(hohlova::edit, _1, _2, _3);
  commands["insert"] = std::bind(hohlova::insert, _1, _2, _3);
  commands["remove"] = std::bind(hohlova::remove, _1, _2, _3);

  hohlova::DictOfDictionary distOfdist;
  std::string cmd;

  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(distOfdist, std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
    return 0;
}
