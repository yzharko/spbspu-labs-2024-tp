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

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& first, const DataStruct& second);
}

#endif
