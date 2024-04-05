#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

namespace psarev
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& is, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
