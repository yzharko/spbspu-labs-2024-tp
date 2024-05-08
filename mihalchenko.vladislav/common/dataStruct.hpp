#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <complex>
#include <iomanip>

namespace mihalchenko
{
  struct DataStruct
  {
    std::string key1_;
    std::complex< double > key2_;
    std::string key3_;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool operator<(const DataStruct &lhs, const DataStruct &rhs);
}

#endif
