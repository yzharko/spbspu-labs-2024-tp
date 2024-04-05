#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace gorbunova
{
  struct delimiter
  {
    char expected;
  };

  std::istream &operator>>(std::istream &in, delimiter &&dest);
}
#endif
