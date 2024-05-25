#ifndef HELPDELIMITERS_HPP
#define HELPDELIMITERS_HPP

#include "details.hpp"

namespace mihalchenko
{
  std::istream &operator>>(std::istream &is, mihalchenko::dict_t &dict);
  std::istream &operator>>(std::istream &is, mihalchenko::dictElement_t &dictElem);
}

#endif
