#include "DelimiterIO.hpp"
#include "iofmtguard.hpp"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c;
  in >> c;
  if (in && std::tolower(c) != std::tolower(dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
