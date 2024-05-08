#include "delimiter.hpp"

std::istream & redko::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (tolower(c) != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
