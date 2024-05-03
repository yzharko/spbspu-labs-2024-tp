#include "typesKeys.hpp"
#include "delimiter.hpp"

namespace nikiforov
{
  std::istream& operator>>(std::istream& in, IntIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

}
