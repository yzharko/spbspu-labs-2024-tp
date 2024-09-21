#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iosfwd>

namespace gorbunova
{
  struct Delimiter
  {
    char expected;
  };

  std::istream &operator>>(std::istream &in, Delimiter &&dest);
}
#endif
