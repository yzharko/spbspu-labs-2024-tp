#include "helpDelimiters.hpp"
#include <algorithm>

std::istream &mihalchenko::operator>>(std::istream &is, dict_t &dict)
{
  // if (is >> pair.first >> pair.second)
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  else
  {
    dictElement_t pair;
    is >> pair;
    auto pointer = dict.find(pair.first);
    if (pointer == dict.end())
    {
      dict.emplace(pair.first, pair.second);
    }
  }
  return is;
}

std::istream &mihalchenko::operator>>(std::istream &is, dictElement_t &dictElem)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  dictElement_t pair;
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
