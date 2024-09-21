#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <unordered_map>
#include "commands.hpp"

using namespace gorbunova;

int main()
{
  std::unordered_map< std::string, std::function< void(const std::vector< std::string > &) > > commands;

  commands["help"] = [](const std::vector< std::string > &)
  { help(); };
  commands["create"] = [](const std::vector< std::string > &args)
  { if (args.size() == 2) create(args[1]); };
  commands["remove"] = [](const std::vector< std::string > &args)
  { if (args.size() == 2) remove(args[1]); };
  commands["clear"] = [](const std::vector< std::string > &args)
  { if (args.size() == 2) clear(args[1]); };
  commands["print"] = [](const std::vector< std::string > &args)
  { if (args.size() == 2) print(args[1]); };
  commands["size"] = [](const std::vector< std::string > &args)
  { if (args.size() == 2) size(args[1]); };
  commands["list"] = [](const std::vector< std::string > &)
  { list(); };
  commands["unite"] = [](const std::vector< std::string > &args)
  { if (args.size() == 4) unite(args[1], args[2], args[3]); };
  commands["add"] = [](const std::vector< std::string > &args)
  { if (args.size() == 3) add(args[1], args[2]); };
  commands["intersection"] = [](const std::vector< std::string > &args)
  { if (args.size() == 4) intersection(args[1], args[2], args[3]); };
  commands["insert"] = [](const std::vector< std::string > &args)
  { if (args.size() == 4) insert(args[1], args[2], args[3]); };
  commands["find"] = [](const std::vector< std::string > &args)
  { if (args.size() == 3) find(args[1], args[2]); };
  commands["change"] = [](const std::vector< std::string > &args)
  { if (args.size() == 4) change(args[1], args[2], args[3]); };
  commands["findLetter"] = [](const std::vector< std::string > &args)
  { if (args.size() == 3 && args[2].size() == 1) findLetter(args[1], args[2][0]); };
  commands["delete"] = [](const std::vector< std::string > &args)
  { if (args.size() == 3) deleteElem(args[1], args[2]); };

  std::string input;
  std::cout << "Enter command: ";
  std::getline(std::cin, input);
  while (input != "exit" && !std::cin.eof())
  {
    std::istringstream iss(input);
    std::vector< std::string > tokens;
    std::string token;
    while (iss >> token)
    {
      tokens.push_back(token);
    }
    if (tokens.empty())
      continue;

    const std::string &cmd = tokens[0];
    auto it = commands.find(cmd);
    if (it != commands.end())
    {
      it->second(tokens);
    }
    else
    {
      std::cout << "Invalid command or number of parameters\n";
    }
    std::cout << "Enter command: ";
    std::getline(std::cin, input);
  }

  return 0;
}
