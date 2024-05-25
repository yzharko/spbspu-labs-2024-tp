#include "helpDelimiters.hpp"
#include <algorithm>

std::istream &mihalchenko::operator>>(std::istream &is, mihalchenko::dict_t &dict)
{
  mihalchenko::dictElement_t pair("", 0);
  // if (is >> pair.first >> pair.second)
  if (is >> pair)
  {
    auto pointer = dict.find(pair.first);
    if (pointer == dict.end())
    {
      dict.emplace(pair.first, pair.second);
    }
  }
  return is;
}

std::istream &mihalchenko::operator>>(std::istream &is, mihalchenko::dictElement_t &dictElem)
{
  mihalchenko::dictElement_t pair("", 0);
  is >> pair.first >> pair.second;
  if (is)
  {
    dictElem = pair;
  }
  return is;
}

bool mihalchenko::operator==(const dictElement_t &dictElem1, const dictElement_t &dictElem2)
{
  return ((dictElem1.first == dictElem2.first) && (dictElem1.second == dictElem2.second));
}
