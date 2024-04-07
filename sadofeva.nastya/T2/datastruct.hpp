#ifndef DATASTRUCT_HPP
#define DATASTRUST_HPP
#include <string>
#include <iostream>
#include "delimiter.hpp"

namespace sadofeva
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream & is, DataStruct& value);
  std::ostream & operator<<(std::ostream & out, const DataStruct & src);
  std::istream & operator>>(std::istream & is, DoubleIO && dest);
  std::istream & operator>>(std::istream & is, DelimiterIO && dest);
  std::istream & operator>>(std::istream & is, UnsignedLongLongIO && dest);
  std::istream & operator>>(std::istream & is, StringIO && dest);
  bool operator<(const DataStruct & one, const DataStruct & two);
}

#endif
