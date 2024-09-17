#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <string>

namespace jirkov
{
  using dictionary = std::multimap< std::string, std::string >;
  void help();
  void create();
  void remove();
  void print();
  void sort();
  void sortByFrequency();
  void sortByAlphabet();
  void deleteKey();
  void findKey();
  void openFile();
}

#endif
