#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <complex>

namespace gorbunova
{
  struct DataStruct
  {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  struct complexx
  {
    std::complex<double> &ref;
  };

  struct ratio
  {
    std::pair<long long, unsigned long long> &ref;
  };

  struct str
  {
    std::string &ref;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool operator<(const DataStruct &lhs, const DataStruct &rhs);
  std::istream &operator>>(std::istream &in, complexx &&dest);
  std::istream &operator>>(std::istream &in, ratio &&dest);
  std::istream &operator>>(std::istream &in, str &&dest);
}
#endif
