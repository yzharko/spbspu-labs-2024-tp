#ifndef DELIMETOR_HPP
#define DELIMETOR_HPP

#include <iostream>

namespace kaseev
{
  struct Delimiter {
    char expected;
  };

  struct DblLit
  {
    double & ref;
  };

  struct UllOct
  {
    unsigned long long & ref;
  };

  struct String
  {
    std::string & ref;
  };

  std::istream &operator>>(std::istream &is, Delimiter &&exp);
}

#endif
