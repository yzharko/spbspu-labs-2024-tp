#include "helpFunctions.hpp"
#include <iostream>
#include <string>

std::string mihalchenko::getDictName(std::string &str)
{
  return str.substr(0, str.find(".txt"));
}

size_t mihalchenko::getSize(mapOfDicts_t &mapOfDictionaries,
                            const std::string &nameOfDict)
{
  size_t size = 0;
  for (auto iter = mapOfDictionaries.cbegin(); iter != mapOfDictionaries.cend(); ++iter)
  {
    if (iter->first == nameOfDict)
    {
      for (auto iterDictElem = iter->second.cbegin();
           iterDictElem != iter->second.cend(); ++iterDictElem)
      {
        size++;
      }
      break;
    }
  }
  return size;
}

std::ostream &mihalchenko::printInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>" << '\n';
  return out;
}

std::ostream &mihalchenko::printErrorMessage(std::ostream &out)
{
  out << "ERROR" << '\n';
  return out;
}
