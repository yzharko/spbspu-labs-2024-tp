#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <istream>
#include <ostream>

namespace lisitsyna
{
  struct DataStruct
  {
    long long key1;
    char key2;
    std::string key3;
  };
  bool compare(const DataStruct& rh, const DataStruct& lh);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}
#endif
