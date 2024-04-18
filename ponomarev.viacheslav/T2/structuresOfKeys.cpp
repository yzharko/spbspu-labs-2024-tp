#include "structuresOfKeys.hpp"
#include "delimiter.hpp"
#include <cmath>

std::istream &ponomarev::operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string num;
  std::getline(in, num, ':');
  if ((num[1] != '.') || !(std::isdigit(num[0])))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  size_t posE = num.find('e');
  if (posE == std::string::npos)
  {
    size_t posE = num.find('E');
    if (posE == std::string::npos)
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }
  if ((num[posE + 1] != '+') && (num[posE + 1] != '-'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  for (size_t i = 2; i < posE; i++)
  {
    if (!(std::isdigit(num[i])))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  for (size_t i = posE + 2; i < num.length(); i++)
  {
    if (!(std::isdigit(num[i])))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  dest.ref = std::stod(num);
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, LongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::getline(in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' }, dest.ref, ':');
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}
