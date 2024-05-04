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

  std::istream &operator>>(std::istream &in, yaDataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const yaDataStruct &dest);
  bool operator<(const yaDataStruct & lhs, const yaDataStruct & rhs);
}

#endif
