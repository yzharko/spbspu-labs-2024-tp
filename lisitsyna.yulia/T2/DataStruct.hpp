#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>

namespace lisitsyna
{
  struct Data
  {
    long long key1;
    char key2;
    std::string key3;
  };

  bool comp(const Data& rh, const Data& lh);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
}

#endif
