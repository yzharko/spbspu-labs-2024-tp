#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <string>

namespace doroshenko
{
  using dictionary = std::map< std::string, std::string >;
  void help(std::istream& input, std::ostream& output);
  void createDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void removeDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void printDict(const std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortByFrequency(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortByAlphabet(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void deleteKey(dictionary& dict, std::istream& input, std::ostream& output);
  void findKey(dictionary& dict, std::istream& input, std::ostream& output);
  void openFile(dictionary& dict, std::istream& input, std::ostream& output);
  void writeToFile(const std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void warning(std::ostream& output, const std::string& mes);
}

#endif
