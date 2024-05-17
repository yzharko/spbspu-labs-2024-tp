#include <iostream>
#include <fstream>
#include <functional>
#include <limits>

#include "commands.hpp"
#include "details.hpp"

int main()
{
  setlocale(LC_ALL, "ru");
  std::cout << "Чтобы вывести все команды, введите 'help'\n";
  mihalchenko::dictElement element;
  std::map<std::string, std::function<void(mihalchenko::dictElement &, std::istream &, std::ostream &)>>
      cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(mihalchenko::help, _3);
  }
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(element, std::cin, std::cout);
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
