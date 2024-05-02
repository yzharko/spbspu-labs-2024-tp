#include "taskTypes.hpp"
#include "delim.hpp"

using delim = psarev::DelimiterIO;

std::istream& psarev::operator>>(std::istream& in, intIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
}
