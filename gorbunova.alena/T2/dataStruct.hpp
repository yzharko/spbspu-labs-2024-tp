#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>

namespace gorbunova
{
  struct DataStruct
  {
    std::complex< double > key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  struct Complexx
  {
    std::complex< double > &ref;
  };

  struct Ratio
  {
    std::pair<long long, unsigned long long> &ref;
  };

  struct Str
  {
    std::string &ref;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool operator<(const DataStruct &lhs, const DataStruct &rhs);
  std::istream &operator>>(std::istream &in, Complexx &&dest);
  std::istream &operator>>(std::istream &in, Ratio &&dest);
  std::istream &operator>>(std::istream &in, Str &&dest);
}
#endif
