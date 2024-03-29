#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <utility>
#include <string>
#include <iostream>

namespace miheev
{
  using real = std::pair<long long, unsigned long long>;
  struct DataStruct
  {
    long long key1;
    real key2;
    std::string key3;
  };
  struct DelimiterI
  {
    char expected;
  };
  std::ostream& operator>>(std::istream& is, DelimiterI&& exp);
  std::istream& operator>>(std::istream& is, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
}

#endif
