#include "structs.hpp"
#include "delimeterI.hpp"

std::istream& operator>>(std::istream& is, unsignedLongLong&& dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> std::hex >> dest.value;
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
  dest.ref.Re(Re);
  dest.ref.Im.(Im);
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
