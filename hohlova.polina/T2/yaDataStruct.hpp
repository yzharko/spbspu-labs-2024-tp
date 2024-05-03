#ifndef YADATASTRUCT_HPP
#define YADATASTURCT_HPP
#include <complex>
#include <cassert>
#include <iomanip>

namespace hohlova
{
  using real = std::pair<long long, unsigned long long>;
  using sll = long long;
  using ull = unsigned long long;

  struct Data
  {
    real key1;
    std::complex< double > key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);

  bool operator<(const Data& lhs, const Data& rhs);
  bool operator<(const real& leftReal, const real& rightReal);
};

#endif
