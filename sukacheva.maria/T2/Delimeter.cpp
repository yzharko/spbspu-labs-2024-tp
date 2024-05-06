#include "Delimeter.hpp"
#include <iostream>

std::istream& sukacheva::operator>>(std::istream& is, Delimeter&& val)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = '0';
  is >> c;
  if (c != val.del)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}
