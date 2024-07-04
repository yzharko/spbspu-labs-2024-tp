#ifndef DELIMETER_HPP
#define DELIMETER_HPP
#include <iostream>

namespace taskaev
{
  struct DelimeterI
  {
    char expected;
  };

  std::istream& operator>>(std::istream& is, DelimeterI&& exp);
}
#endif
