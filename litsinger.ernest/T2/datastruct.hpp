#ifndef LIST2_0_DATASTRUCT_HPP
#define LIST2_0_DATASTRUCT_HPP
#include <string>
#include <iostream>
#include "dataTypes.h"

namespace litsinger
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& value);
  std::ostream& operator<<(std::ostream& os, const DataStruct& myStruct);
  bool operator<(const DataStruct& left, const DataStruct& right);

}

#endif
