#include "delimiter.hpp"

std::istream & gorbunova::operator>>(std::istream &in, delimiter &&dest)
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
