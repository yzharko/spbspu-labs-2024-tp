#ifndef DATASTRUST
#define DATASTRUCT
#include <string>
#include <utility>
#include <iostream>
#include "io_structures.hpp"
#include "scope_guard.hpp"

namespace kovshikov
{
  struct DataStruct
  {
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream &is, DataStruct &value);
  std::ostream & operator<<(std::ostream & out, const DataStruct &value);
  bool operator>(const DataStruct &left, const DataStruct &right);
 // bool operator<(const DataStruct &value);
}

#endif
