#include "DelAnd.hpp"
#include <iostream>

std::istream & susidko::operator>>(std::istream & in, susidko::DelimiterI && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & susidko::operator>>(std::istream & in, susidko::LongLong_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> exp.key1_;
  return in;
}

std::istream & susidko::operator>>(std::istream & in, susidko::UnsignedLLBin_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> exp.key2_;
  return in;
}

std::istream & susidko::operator>>(std::istream & in, susidko::String_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  getline(in, exp.key3_, '"');
  return in;
}
