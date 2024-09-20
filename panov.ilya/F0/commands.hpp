#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ios>
#include "dicts.hpp"

namespace panov
{
  std::ostream & help(std::istream &, std::ostream &);
  std::ostream & create(dicts_t &, std::istream &, std::ostream &);
  std::ostream & add(dicts_t &, std::istream &, std::ostream &);
  std::ostream & deleteWord(dicts_t &, std::istream &, std::ostream &);
  std::ostream & change(dicts_t &, std::istream &, std::ostream &);
  std::ostream & reset(dicts_t &, std::istream &, std::ostream &);
  std::ostream & print(dicts_t &, std::istream &, std::ostream &);
  std::ostream & intersection(dicts_t &, std::istream &, std::ostream &);
  std::ostream & get(dicts_t &, std::istream &, std::ostream &);
  std::ostream & search(dicts_t &, std::istream &, std::ostream &);
  std::ostream & addline(std::istream &, std::ostream &);
}
#endif
