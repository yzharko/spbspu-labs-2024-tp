#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace popov
{
  struct DelimiterIO
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, DelimiterIO && exp);
}

#endif
