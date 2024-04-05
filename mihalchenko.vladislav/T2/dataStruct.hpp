#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
// #include <complex>
#include <iomanip> // setpresition()
#include "delimiters.hpp"

namespace mihalchenko
{
  struct DataStruct
  {
    // DataStruct(int key1, std::complex<double> key2, std::string key3) : key1_(key1), key2_(key2), key3_(key3){};
    // DataStruct(int key1, int key2, std::string key3) : key1_(5), key2_(5), key3_("key3"){};
    std::string key1_;
    std::complex<double> key2_;
    // int key2_;
    std::string key3_;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);

  bool operator<(const DataStruct &lhs, const DataStruct &rhs);
}

#endif
