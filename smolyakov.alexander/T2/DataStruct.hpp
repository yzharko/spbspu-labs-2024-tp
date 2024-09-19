#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

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
}

#endif
