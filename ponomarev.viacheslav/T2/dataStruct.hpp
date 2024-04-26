#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <cstring>
#include <iostream>

namespace ponomarev
{
  struct DataStruct
  {
    std::string key1;
    std::string key2;
    std::string key3;
  };

  struct yaDataStruct
  {
    std::string key2;
    std::pair< long long, unsigned long long > key4;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
  bool operator<(const DataStruct & lhs, const DataStruct & rhs);
}

#endif
