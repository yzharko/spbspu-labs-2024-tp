#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iosfwd>
#include "dataTypes.hpp"

namespace litsinger
{
  struct DataStruct
  {
    unsigned long long key1_bin;
    std::string key1_str;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& value);
  std::ostream& operator<<(std::ostream& os, const DataStruct& myStruct);
  bool operator<(const DataStruct& left, const DataStruct& right);

}

#endif
