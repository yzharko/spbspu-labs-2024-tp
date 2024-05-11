#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>
#include "anotherStructs.hpp"

namespace gorbunova
{
  struct YaDataStruct
  {
    std::pair< long long, unsigned long long > key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, YaDataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const YaDataStruct &dest);
  bool operator<(const YaDataStruct &lhs, const YaDataStruct &rhs);
  std::istream &operator>>(std::istream &in, Ratio &&dest);
  std::istream &operator>>(std::istream &in, Str &&dest);
  std::istream &operator>>(std::istream &in, Ull &&dest);
}
#endif
