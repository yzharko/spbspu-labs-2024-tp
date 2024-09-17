#ifndef DELIMITER_HPP
#define DELIMITER_HPP

#include <iosfwd>

namespace malanin
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif