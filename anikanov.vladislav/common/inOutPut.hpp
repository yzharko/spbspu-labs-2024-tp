#ifndef INOUTPUT_HPP
#define INOUTPUT_HPP

#include <iosfwd>
#include "delimiterIO.hpp"

namespace anikanov {
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}

#endif
