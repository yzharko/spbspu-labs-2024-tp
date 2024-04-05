#ifndef DATASTRUCT_HPP
#define DATASTRUST_HPP
#include <string>
#include <iostream>

namespace sadofeva
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator >> (std::istream & in, DataStruct& value);
  std::ostream & operator << (std::ostream & out, const DataStruct & src);
  std::istream & operator >> (std::istream & in, DoubleIO && dest);
  std::istream & operator >> (std::istream & in, DelimiterIO && dest);
  std::istream & operator >> (std::istream & in, UnsignedLongLongIO && dest);
  std::istream & operator >> (std::istream & in, StringIO && dest);
  bool operator < (const DataStruct & one, const DataStruct & two);
}

#endif
