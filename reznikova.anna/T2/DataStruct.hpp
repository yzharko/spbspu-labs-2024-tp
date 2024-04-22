#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include "Keys.hpp"

namespace reznikova
{

  struct DataStruct
  {
    DataStruct():
      key1(0),
      key2(0),
      key3(0)
    {}
    DataStruct(unsigned long long key1_, std::complex<double> key2_, std::string key3_):
      key1(key1_),
      key2(key2_),
      key3(key3_)
    {}
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  bool operator<(const DataStruct & first, const DataStruct & second);
  std::istream & operator>>(std::istream & is, DataStruct & value);
  std::ostream & operator<<(std::ostream & out, const DataStruct & value);
}
#endif
