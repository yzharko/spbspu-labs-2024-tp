#ifndef DICT_HPP
#define DICT_HPP
#include <string>
#include <vector>
#include <map>

namespace zheleznyakov
{
  using wordcoord_t = std::pair < size_t, size_t >;
  using wordpair_t = std::vector < wordcoord_t >;
  using wordpairs_t = std::map< std::string, wordpair_t >;
  using string_t = std::pair< std::string, wordpairs_t >;
  using strings_t = std::map< std::string, string_t >;

  size_t getWordsCount(std::string);
  size_t getLinesCount(std::string);

  wordpairs_t getDict(const std::string &);
  bool isPunctuationMark(const char c);
}
#endif
