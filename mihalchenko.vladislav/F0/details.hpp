#ifndef DETAILS_HPP
#define DETAILS_HPP
#include <map>
#include <string>
#include <iostream>

namespace mihalchenko
{
  using dictElement_t = std::pair<std::string, size_t>;
  using dict_t = std::map<std::string, size_t>;
  using mapOfDicts_t = std::map<std::string, std::map<std::string, size_t>>;
  using mapOfDicts_t = std::pair<std::string, std::map<std::string, size_t>>;
  using pair_t = std::pair<std::string, size_t>;
}

#endif
