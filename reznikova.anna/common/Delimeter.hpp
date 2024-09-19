#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace reznikova
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, reznikova::Delimiter && exp);
}

#endif

