#include "commands.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>

using dictionary = std::multimap< std::string, std::string >;

void jirkov::help(std::istream& input, std::ostream& output)
{
  if (input.peek() != '\n')
  {
    throw std::exception();
  }
  output << "1) help ";
  output << "2) create <name>";
  output << "3) remove <name>";
  output << "4) print <name>";
  output << "5) sort <frequency>";
  output << "6) sort <alphabet> <name>";
  output << "7) delete <key>";
  output << "8) find <key>";
}

void jirkov::create(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  if (!input)
  {
    return;
  }
  dicts.emplace(dictName, dictionary());
  dictionary currentDict = dicts[dictName];
  using namespace std::placeholders;
}
