#ifndef DELIM_HPP
#define DELIM_HPP
#include <iomanip>

namespace psarev
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct intIO
  {
    int& ref;
  };

  std::istream& operator>>(std::istream& in, intIO&& dest);
}

#endif
