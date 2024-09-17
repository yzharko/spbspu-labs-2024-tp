#include <iostream>
#include <functional>
#include "commands.hpp"

int main()
{
  setlocale(LC_ALL, "Russian");

  using mapDictionaries_t = std::map< std::string, std::map< std::string, std::vector< size_t > > >;

  mapDictionaries_t mapDictionaries;

  using namespace std::placeholders;
  std::map< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&) > > command;
  {
    command["help"] = std::bind(litsinger::printCommands, _3);
    command["create"] = litsinger::creatDict;
    command["add_word"] = litsinger::addWord;
    command["delete_word"] = litsinger::deleteWord;
    command["reset"] = litsinger::resetDict;
    command["print"] = litsinger::printDict;
    command["add_line"] = litsinger::addLine;
    command["get_print"] = litsinger::getPrint;
    command["get_intersection"] = litsinger::getIntersection;
    command["search_letter"] = litsinger::searchLetter;
  }

  std::string cmd = "";

  std::cout << "Введите любую допустимую команду (команда 'help' для вывода всех доступных команд)\n";
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