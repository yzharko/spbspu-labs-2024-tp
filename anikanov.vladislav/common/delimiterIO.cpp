#include "delimiterIO.hpp"

#include <iomanip>
#include <istream>
#include "iofmtguard.hpp"

std::istream& anikanov::operator>>(std::istream& in, anikanov::DelimiterIO&& dest)
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
