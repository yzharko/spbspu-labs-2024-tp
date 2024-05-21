#ifndef DICT_HPP
#define DICT_HPP
#include <string>
#include <vector>
#include <map>

namespace zheleznyakov
{
  using wordpairs_t = std::map< std::string, std::vector < std::pair < size_t, size_t > > >;
  using string_t = std::pair< std::string, wordpairs_t >;
  using strings_t = std::map< std::string, string_t >;

  size_t getWordsCount(std::string);
  size_t getLinesCount(std::string);

  wordpairs_t getDict(const std::string &);
  bool isPunctuationMark(const char c);
}
#endif
