#ifndef DATASTURCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include <cassert>
#include <iomanip>

namespace hohlova
{
  using real = std::pair< long long, unsigned long long >;
  using sll = long long;
  using ull = unsigned long long;

  struct Data
  {
    double key1;
    real key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);

  bool operator<(const Data& left, const Data& right);
  bool operator<(const real& leftReal, const real& rightReal);
}

#endif
