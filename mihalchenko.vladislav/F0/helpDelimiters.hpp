#ifndef HELPDELIMITERS_HPP
#define HELPDELIMITERS_HPP

#include "details.hpp"

namespace mihalchenko
{
  std::istream &operator>>(std::istream &is, dict_t &dict);
  std::istream &operator>>(std::istream &is, dictElement_t &dictElem);
  bool operator==(const dictElement_t &dictElem1, const dictElement_t &dictElem2);
}

#endif
