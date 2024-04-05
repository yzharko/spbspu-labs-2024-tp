#include "taskTypes.hpp"
#include "delim.hpp"

std::istream& psarev::operator>>(std::istream& in, DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  if (!(in >> dest.ref >> DelimiterIO{ 'd' }) && !std::isdigit(dest.ref))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& psarev::operator>>(std::istream& in, UnsignedLongLongIO&& dest)
{

}

std::istream& psarev::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}