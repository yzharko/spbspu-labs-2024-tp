#ifndef DATASTRUCT_HPP
#define DATASTRUST_HPP
#include <iosfwd>
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
  bool operator<(const DataStruct & one, const DataStruct & two);
}

#endif
