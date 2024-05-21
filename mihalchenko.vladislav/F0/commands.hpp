#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iomanip>
#include "helpFunctions.hpp"

namespace mihalchenko
{
  void help(std::ostream &out);
  void open(mapOfDicts_t &mapOfDictionaries, std::istream &is);
  void save(const mapOfDicts_t &mapOfDictionaries, std::istream &is);
}

#endif
