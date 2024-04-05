#include "helpStructs.hpp"

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::Delimitr && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
