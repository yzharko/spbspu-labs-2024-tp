#ifndef DELIM_HPP
#define DELIM_HPP
#include <iostream>

namespace psarev
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
