#include "delimiter.hpp"

std::istream & lisitsyna::operator>>(std::istream & in, Separator && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
