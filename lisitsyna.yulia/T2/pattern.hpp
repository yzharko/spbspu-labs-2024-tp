#ifndef PATTERN_HPP
#define PATTERN_HPP
#include <istream>
#include <string>

namespace lisitsyna
{
  struct SllLit
  {
    long long& value;
  };
  std::istream& operator>>(std::istream& in, BinUll&& num);
  struct ChrLit
  {
    char& value;
  };
  std::istream& operator>>(std::istream& in, HexUll&& num);
  struct StringKey
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StrKey&& value);
}
#endif
