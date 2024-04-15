#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <istream>
#include <string>

namespace lisitsyna
{
  struct SllLit
  {
    long long& ref;
  };
  std::istream& operator>>(std::istream& in, SllLit&& dest);

  struct ChrLit
  {
    char& ref;
  };
  std::istream& operator>>(std::istream& in, ChrLit&& dest);

  struct StringKey
  {
    std::string& ref;
  };
  std::istream& operator>>(std::istream& in, StringKey&& dest);
}
#endif
