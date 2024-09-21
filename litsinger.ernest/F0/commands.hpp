#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <vector>

using mapDictionaries_t = std::map< std::string, std::map< std::string, std::vector< size_t > > >;

namespace litsinger
{
  void printCommands(std::ostream& out);
  void creatDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void addWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void deleteWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void resetDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void printDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void addLine(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void getPrint(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void getIntersection(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  void searchLetter(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
}
#endif
