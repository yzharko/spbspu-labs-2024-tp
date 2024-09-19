#include <functional>
#include "Commands.hpp"

int main()
{
  std::cout << "Enter 'help' to see available commands.\n"
            << "> ";
  Commands cmd{ std::cin, std::cout };
  const std::map<std::string, std::function<void()>> cmdMap{
    { "help", std::bind(&Commands::help, std::ref(cmd)) },
    { "openFile", std::bind(&Commands::openFile, std::ref(cmd)) },
    { "analyze", std::bind(&Commands::analyze, std::ref(cmd)) },
    { "closeFile", std::bind(&Commands::closeFile, std::ref(cmd)) },
    { "print", std::bind(&Commands::print, std::ref(cmd)) },
    { "delete", std::bind(&Commands::deleteKey, std::ref(cmd)) },
    { "exist", std::bind(&Commands::exist, std::ref(cmd)) },
    { "search", std::bind(&Commands::search, std::ref(cmd)) },
    { "showSize", std::bind(&Commands::showSize, std::ref(cmd)) },
    { "remove", std::bind(&Commands::remove, std::ref(cmd)) },
  };

  std::string command;
  std::cin >> command;
  while (!std::cin.eof())
  {
    try
    {
      auto it = cmdMap.find(command);
      if (it != cmdMap.end())
      {
        it->second();
      }
      else
      {
        cmd.invalidCommand();
        std::cin.ignore(256, '\n');
        cmd.help();
      }
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << "\n";
      std::cin.ignore(256, '\n');
    }
    std::cin.clear();
    std::cout << "> ";
    std::cin >> command;
  };
  return 0;
}
