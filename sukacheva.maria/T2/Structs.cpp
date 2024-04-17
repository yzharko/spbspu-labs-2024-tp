#include "Structs.hpp"
#include <iostream>

namespace sukacheva {
  std::istream& operator>>(std::istream& is, LongLongLit&& val)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
  }

  std::istream& operator>>(std::istream& is, DoubleLit&& val)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
  }

  std::istream& operator>>(std::istream& is, String&& val)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
  }
}