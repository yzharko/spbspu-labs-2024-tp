#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iomanip>
#include "helpFunctions.hpp"

namespace mihalchenko
{
  void help(std::ostream &out);
  void create(mapOfDicts_t &mapOfDictionaries, std::istream &is);
  void save(mapOfDicts_t &mapOfDictionaries, std::ostream &out);
  void size(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void view(mapOfDicts_t &mapOfDictionaries, std::ostream &out);
  void find(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void rename(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void deleteDict(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void edit(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void insert(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void remove(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void print(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void clear(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void count(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void merge(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void unique(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
  void swap(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out);
}

#endif
