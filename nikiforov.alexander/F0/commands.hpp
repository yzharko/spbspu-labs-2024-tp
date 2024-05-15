#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iomanip>
#include <map>

using mapDictionaries_t = std::map< std::string, std::map< std::string, size_t > >;

namespace nikiforov
{
  std::string cutNameFile(std::string& str);

  void createDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
  std::map<std::string, size_t> getDictionary(std::istream& in);

  void deleteDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void add(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void unite(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void rename(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void clear(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);
}

#endif
