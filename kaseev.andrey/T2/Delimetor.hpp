#ifndef DELIMETOR_HPP
#define DELIMETOR_HPP

#include <iostream>

namespace kaseev
{
  struct Delimiter {
    char expected;
  };

  std::istream &operator>>(std::istream &is, Delimiter &&exp);
}

#endif
