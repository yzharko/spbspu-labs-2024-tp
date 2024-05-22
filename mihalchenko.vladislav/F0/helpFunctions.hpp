#ifndef HELPFUNCTIONS_HPP
#define HELPFUNCTIONS_HPP

#include "details.hpp"

namespace mihalchenko
{
  std::string getDictName(std::string &str);
  size_t getSize(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict);
  std::ostream &printInvalidCommand(std::ostream &out);
  std::ostream &printErrorMessage(std::ostream &out);
}

#endif
