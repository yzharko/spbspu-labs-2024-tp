#ifndef DELIMITERIO_HPP
#define DELIMITERIO_HPP

#include <iosfwd>

namespace anikanov {
  struct DelimiterIO {
    char exp;
  };

  std::istream& operator>>(std::istream& in, anikanov::DelimiterIO&& dest);
}

#endif
