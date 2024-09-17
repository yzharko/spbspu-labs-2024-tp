#include "delimiter.hpp"
#include <iostream>

std::istream &malanin::operator>>(std::istream &in, DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '0';
  in >> c;
  if (tolower(c) != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}