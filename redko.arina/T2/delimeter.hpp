#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace redko
{
  struct DelimiterIO
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
}

#endif
