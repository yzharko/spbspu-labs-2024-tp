#ifndef DICT_HPP
#define DICT_HPP
#include <string>
#include <map>

namespace zheleznyakov
{
  using string_t = std::map< std::string, std::map< std::string, size_t > >;
  using strings_t = std::map< std::string, string_t >;

  size_t getWordsCount(std::string);
  size_t getLinesCount(std::string);
}
#endif
