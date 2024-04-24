#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <cstring>
#include <iostream>

namespace ponomarev
{
  struct Data
  {
    std::string key1;
    std::string key2;
    std::string key3;
  };

  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
  bool operator<(const Data & lhs, const Data & rhs);
}

#endif
