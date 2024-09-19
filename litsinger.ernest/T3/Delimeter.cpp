#include "Delimeter.hpp"

std::istream & litsinger::operator>>(std::istream & is, litsinger::Delimiter && exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

