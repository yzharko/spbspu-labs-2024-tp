#include "taskTypes.hpp"
#include "delim.hpp"

using delim = psarev::DelimiterIO;

std::istream& psarev::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return in >> dest.ref;
}

std::istream& psarev::operator>>(std::istream& in, UllHexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string strHexPart = "";
  in >> delim{ '0' } >> delim{ 'x' } >> std::hex >> dest.ref;
  return in;
}

std::istream& psarev::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> delim{ '"' }, dest.ref, '"');
}
