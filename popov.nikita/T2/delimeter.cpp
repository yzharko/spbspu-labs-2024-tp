#include "delimeter.hpp"

std::istream & popov::operator>>(std::istream& is, popov::DelimiterIO && exp)
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
