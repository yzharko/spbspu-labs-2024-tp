#ifndef INDELIM_HPP
#define INDELIM_HPP

#include <iosfwd>
#include "delimiter.hpp"

namespace anikanov {
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif
