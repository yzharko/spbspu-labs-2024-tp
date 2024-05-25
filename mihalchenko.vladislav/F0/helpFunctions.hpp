#ifndef HELPFUNCTIONS_HPP
#define HELPFUNCTIONS_HPP

#include "details.hpp"

namespace mihalchenko
{
  std::string getDictName(std::string &str);
  size_t getSize(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict);
  void sortByFreq(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict);
  bool compareElemByFreq(const pair_t &iterOfElem1, const pair_t &iterOfElem2);
  std::ostream &printInvalidCommand(std::ostream &out);
  std::ostream &printErrorMessage(std::ostream &out);
}

#endif
