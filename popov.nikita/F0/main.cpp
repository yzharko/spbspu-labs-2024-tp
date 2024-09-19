#include <map>
#include <functional>
#include <exception>
#include <iostream>
#include "commands.hpp"

int main()
{
  using namespace popov;
  using indictionary = std::map< std::string, size_t >;
  using outdictionary = std::map< std::string, indictionary >;
  outdictionary dictionaries;
  std::map< std::string, std::function< void(outdictionary& dictionaries, std::istream& in, std::ostream& out)> > cmds;
  {
    using namespace std::placeholders;
    cmds["help"] = std::bind(helpCmd, _3);
    cmds["create"] = std::bind(createCmd, _1, _2, _3);
    cmds["addWord"] = std::bind(addWordCmd, _1, _2, _3);
    cmds["removeWord"] = std::bind(removeWordCmd, _1, _2, _3);
    cmds["getFrequency"] = std::bind(getFrequencyCmd, _1, _2, _3);
    cmds["topWords"] = std::bind(topWordsCmd, _1, _2, _3);
    cmds["reset"] = std::bind(resetCmd, _1, _2, _3);
    cmds["delete"] = std::bind(deleteCmd, _1, _2, _3);
    cmds["addWordFrequency"] = std::bind(addWordFrequencyCmd, _1, _2, _3);
    cmds["increaseFrequency"] = std::bind(increaseFrequencyCmd, _1, _2, _3);
    cmds["decreasFrequency"] = std::bind(decreasFrequencyCmd, _1, _2, _3);
    cmds["getWordsWithFrequency"] = std::bind(getWordsWithFrequencyCmd, _1, _2, _3);
    cmds["print"] = std::bind(printCmd, _1, _2, _3);
    cmds["createSame"] = std::bind(createSameCmd, _1, _2, _3);
  }
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(dictionaries, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
