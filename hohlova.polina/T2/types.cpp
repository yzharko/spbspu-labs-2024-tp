#include <iostream>
#include "types.hpp"
#include "delimiter.hpp"

namespace hohlova
{
  using sep = DelimiterIO;
  using label = LabelIO;

  std::istream& operator>>(std::istream& in, ULLIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> std::hex >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    double re = 0;
    double im = 0;
    in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> re >> im >> DelimiterIO{ ')' };
    if (in)
    {
      dest.ref.real(re);
      dest.ref.imag(im);
    }
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
