#ifndef INTERNAL_FUNCS_HPP
#define INTERNAL_FUNCS_HPP
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using storage_t = std::map< std::string, std::vector< std::string > >;

namespace psarev
{
  std::ostream& outError(std::ostream& out, const std::string& errText);
  storage_t readStorage(std::istream& in);

  void cleanUpWord(std::string& word);
  bool checkLiter(const std::string& word);

  std::string getSpType(std::string& word);
  bool checkType(std::string& word, size_t& endSize, std::vector< std::string >& ends);

  void outDepot(std::string dest, std::ofstream& out, std::map< std::string, storage_t >& depot);

  char letToSound(char let, char letType, bool& softFact);
  bool printSound(std::ostream& out, char sound, bool softFact);
}

#endif
