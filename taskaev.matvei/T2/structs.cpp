#include "structs.hpp"
#include "delimeter.hpp"

namespace taskaev
{
  std::istream& operator>>(std::istream& is, unsignedLongLongI&& dest)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    return is >> std::hex >> dest.ref;
  }

  std::istream& operator>>(std::istream& is, complexI&& dest)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    double Re;
    double Im;
    is >> DelimeterI{ '#' } >> DelimeterI{ 'c' };
    is >> DelimeterI{ '(' } >> Re >> Im >> DelimeterI{ ')'};
    dest.ref.real(Re);
    dest.ref.imag(Im);
    return is;
  }


  std::istream& operator>>(std::istream& is, stringI&& dest)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    return std::getline(is >> DelimeterI{ '"' }, dest.ref, '"');
  }
}
