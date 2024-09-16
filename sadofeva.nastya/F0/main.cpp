#include <iostream>
#include <functional>
#include <limits>
#include "processor.hpp"
#include "command.hpp"

int main()
{
  using namespace sadofeva;
  dictionaryOfNames dictionaries;
  CommandProcessor commandProcessor;

  try
  {
    sadofeva::printHelp(dictionaries, std::cin, std::cout);
  }
  catch (const std::logic_error& e)
  {
    std::cout << "Error: " << e.what() << '\n';
    skipUntilNewLine(std::cin);
  }

  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      commandProcessor.processCommand(dictionaries, cmd, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << "Error: " << e.what() << '\n';
      skipUntilNewLine(std::cin);
    }
  }
  return 0;
}
