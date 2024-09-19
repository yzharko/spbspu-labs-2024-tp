#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iosfwd>
#include <string>

namespace khomichenko
{

  struct DelimiterIO
  {
    char exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif
