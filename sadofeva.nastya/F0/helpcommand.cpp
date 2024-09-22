#include <stdexcept>
#include <limits>
#include "helpcommand.hpp"

namespace sadofeva
{
  void printError(std::ostream&)
  {
    throw std::logic_error("Incorrect command");
  }

  void skipUntilNewLine(std::istream& in)
  {
    in.clear();
    auto maxstream = std::numeric_limits< std::streamsize >::max();
    in.ignore(maxstream, '\n');
  }

  bool searchDict(const dictionaryOfNames& dictionaries, const std::string& dict_name)
  {
    return dictionaries.find(dict_name) != dictionaries.end();
  }

  bool searchWrd(const Dictionary& dictionary, const std::string& word)
  {
    return dictionary.find(word) != dictionary.end();
  }

  bool compareFrequency(const std::pair< std::string, size_t >& a, const std::pair< std::string, size_t >& b)
  {
    return a.second > b.second;
  }

  void validateDictExists(const dictionaryOfNames& dictionaries, const std::string& dict_name)
  {
    if (!searchDict(dictionaries, dict_name))
    {
      throw std::logic_error("Dictionary \"" + dict_name + "\" does not exist.");
    }
  }
}
