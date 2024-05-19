#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <vector>
#include <memory>
#include <functional>
#include "mycommands.hpp"

int main()
{
  std::cout << "Для просмотра доступных команд введите \"commands\"\n";
  std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > >
  myContainer(new std::vector< std::pair<std::string, std::multimap< size_t, std::string > > >());
  std::map< std::string, std::function< void(std::istream & in, std::ostream & out) > > cmds;
  cmds["commands"] = sobolevsky::getCommands;
  cmds["loadAndCreate"] = std::bind(sobolevsky::getLoadAndCreate, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["allDicts"] = std::bind(sobolevsky::getAllDicts, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["delete"] = std::bind(sobolevsky::getDelete, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["select"] = std::bind(sobolevsky::getSelect, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["rename"] = std::bind(sobolevsky::getRename, myContainer, std::placeholders::_1, std::placeholders::_2);
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch(const std::out_of_range & e)
    {
      sobolevsky::error(std::cout, "ERROR: INVALID COMMAND\n");
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch(const std::invalid_argument & e)
    {
      sobolevsky::error(std::cout, e.what());
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
