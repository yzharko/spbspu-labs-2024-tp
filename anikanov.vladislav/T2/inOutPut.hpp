#ifndef INOUTPUT_HPP
#define INOUTPUT_HPP

#include <iosfwd>
#include "delimiterIO.hpp"
#include "../T2/ullBinIO.hpp"
#include "../T2/ullLitIO.hpp"
#include "../T2/stringIO.hpp"
#include "../T2/delStrIO.hpp"
#include "../T2/dataStruct.hpp"

namespace anikanov {
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, UllBinIO &&dest);
  std::istream &operator>>(std::istream &in, UllLitIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelStrIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}

#endif
