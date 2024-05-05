#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

namespace popov
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream & operator>>(std::istream& is, DataStruct & number);
  std::ostream & operator<<(std::ostream& out, const DataStruct & number);
  bool operator<(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
