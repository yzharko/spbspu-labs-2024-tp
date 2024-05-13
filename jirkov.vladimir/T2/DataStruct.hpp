#ifndef DATASTRUST_HPP
#define DATASTRUCT_HPP
#include <string>
#include <utility>
namespace jirkov
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  bool operator>(const DataStruct &left, const DataStruct &rigth);
  bool operator<(const DataStruct &left, const DataStruct &rigth);
}

#endif
