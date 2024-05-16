#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include "Delimetor.hpp"
#include "ScopeGuard.hpp"

namespace kaseev {
  struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);
  bool operator<(const DataStruct& first, const DataStruct& second);
  std::istream & operator>>(std::istream & in, DblLit && data);
  std::istream & operator>>(std::istream & in, UllOct && data);
  std::istream& operator>>(std::istream& in, String && dest);
}
#endif
