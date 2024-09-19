#include "IOstructures.hpp"
#include "DelimiterIO.hpp"
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
