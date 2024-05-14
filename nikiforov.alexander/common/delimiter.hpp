#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iomanip>

namespace nikiforov
{
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
