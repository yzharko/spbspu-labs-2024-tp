#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <istream>
#include <string>
#include <utility>

namespace smolyakov
{
  struct DataStruct
  {
    std::pair<long long, unsigned long long> key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream& operator >> (std::istream& inputStream, smolyakov::DataStruct& data);
}

#endif

