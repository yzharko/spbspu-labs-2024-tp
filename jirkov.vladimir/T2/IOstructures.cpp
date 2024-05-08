#include "IOstructures.hpp"
#include <iostream>

std::istream & jirkov::operator>>(std::istream & in, DelimiterIO && value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char ch = 0;
  in >> ch;
  if (ch != value.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & jirkov::operator>>(std::istream & in, UllLitIO && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  in >> value.ref >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
}

std::istream & jirkov::operator>>(std::istream & in, /*key2*/ && value)
{
  return in;
}

std::istream & jirkov::operator>>(std::istream & in, StringIO && value)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, value.str, '"');
}
