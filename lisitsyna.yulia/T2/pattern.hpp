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
  std::istream& operator>>(std::istream& in, SllLit&& num);
  struct ChrLit
  {
    char& value;
  };
  std::istream& operator>>(std::istream& in, ChrLit&& num);
  struct StringKey
  {
    std::string& value;
  };
  std::istream& operator>>(std::istream& in, StringKey&& value);
}
#endif
