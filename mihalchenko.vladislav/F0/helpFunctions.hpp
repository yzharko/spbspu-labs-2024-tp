#ifndef HELPFUNCTIONS_HPP
#define HELPFUNCTIONS_HPP

#include "details.hpp"

namespace mihalchenko
{
  std::string getDictName(std::string &str);
  void sortByFreq(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict, std::istream &is, std::ostream &out);
  void sortByAlph(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict, std::istream &is, std::ostream &out);
  bool compareElemByFreq(const pair_t &iterOfElem1, const pair_t &iterOfElem2);
  bool compareElemByAlph(const pair_t &iterOfElem1, const pair_t &iterOfElem2);
  std::ostream &printInvalidCommand(std::ostream &out);
  std::ostream &printErrorMessage(std::ostream &out);
  std::ostream &printWrongInput(std::ostream &out);
  void findUnique(mapOfDicts_t &mapOfDictionaries, dict_t &newDict,
                    const std::string &nameOfDict1, const std::string &nameOfDict2, std::ostream &out);
}

#endif
