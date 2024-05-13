#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>

namespace nikiforov
{
  struct Data
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
  bool operator<(const Data& first, const Data& second) noexcept;
}

#endif
