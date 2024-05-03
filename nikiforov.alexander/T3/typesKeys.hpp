#ifndef TYPESKEYS_HPP
#define TYPESKEYS_HPP
#include <string>

namespace nikiforov
{
  struct IntIO
  {
    int& ref;
  };

  std::istream& operator>>(std::istream& in, IntIO&& dest);
}

#endif
