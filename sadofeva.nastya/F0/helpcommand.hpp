#ifndef HELPCOMMAND_HPP
#define HELPCOMMAND_HPP

#include <iostream>
#include <map>

namespace sadofeva
{
  using Dictionary = std::map< std::string, size_t >;
  using dictionaryOfNames = std::map< std::string, Dictionary >;

  bool searchDict(const dictionaryOfNames& dictionaries, const std::string& dict_name);
  bool searchWrd(const Dictionary& dictionaries, const std::string& word);
  bool compareFrequency(const std::pair< std::string, size_t >& a, const std::pair< std::string, size_t >& b);
  void validateDictExists(const dictionaryOfNames& dictionaries, const std::string& dict_name);
  void printError(std::ostream& out);
  void skipUntilNewLine(std::istream& in);
}

#endif
