#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace litsinger
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, litsinger::Delimiter && exp);
}

#endif

