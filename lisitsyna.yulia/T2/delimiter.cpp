#include "delimiter.hpp"
#include <iostream>

lisitsyna::Delimiter::Delimiter(char exp) :
  exp(exp)
{}

std::istream& lisitsyna::operator>>(std::istream& in, Delimiter&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
