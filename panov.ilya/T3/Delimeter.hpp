#ifndef DELIMETER_HPP
#define DELIMETER_HPP

#include <iostream>

namespace panov
{
  struct Delimeter
  {
    const char* expected;
  };

  std::istream& operator>>(std::istream& in, Delimeter&& exp);
}

#endif
