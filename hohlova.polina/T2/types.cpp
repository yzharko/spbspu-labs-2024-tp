#include "types.hpp"
#include "delimiter.hpp"

namespace hohlova
{
  using sep = DelimiterIO;
  using label = LabelIO;

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{ 'd' };
  }

  std::istream& operator>>(std::istream& in, RealIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> sep{ '(' } >> sep{ ':' } >> label{ "N" };
    in >> dest.ref.first;
    in >> sep{ ':' } >> label{ "D" };
    in >> dest.ref.second;
    in >> sep{ ':' } >> sep{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }
}
