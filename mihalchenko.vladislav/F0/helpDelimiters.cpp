#include "helpDelimiters.hpp"
#include <algorithm>

std::istream &mihalchenko::operator>>(std::istream &is, mihalchenko::dict_t &dict)
{
  mihalchenko::pair_t pair("", 0);
  if (is >> pair.first >> pair.second)
  {
    auto pointer = dict.find(pair.first);
    if (pointer == dict.end())
    {
      dict.emplace(pair.first, pair.second);
    }
  }
  return is;
}
