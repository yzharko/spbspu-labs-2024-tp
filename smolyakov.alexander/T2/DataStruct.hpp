#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>
#include <utility>

namespace smolyakov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  bool operator < (const DataStruct& first, const DataStruct& second);

  std::istream& operator >> (std::istream& inputStream, DataStruct& data);
  std::ostream& operator << (std::ostream& outputStream, const DataStruct& data);
}

#endif

