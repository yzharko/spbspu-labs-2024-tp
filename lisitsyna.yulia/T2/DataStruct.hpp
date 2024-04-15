#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace lisitsyna
{
  struct Data
  {
    long long key1;
    char key2;
    std::string key3;
  };

  bool operetor(const Data& first, const Data& second);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
}

#endif
