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
  if (!(in >> dest.ref >> delim{ 'd' }) && !(std::isdigit(dest.ref)))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& psarev::operator>>(std::istream& in, UllHexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  if (!(in >> delim{ '0' } >> delim{ 'x' } >> dest.ref) && !std::isdigit(dest.ref))
  {
    in.setstate(std::ios::failbit);
  }
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