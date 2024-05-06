#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

namespace sukacheva {
  struct DataStruct
  {
    double key1;
    long long key2;
    std::string key3;
  };
  std::istream& operator>>(std::istream& is, DataStruct& val);
  std::ostream& operator<<(std::ostream& out, const DataStruct& val);
  bool operator<(const DataStruct& left, const DataStruct& right);
}

#endif
