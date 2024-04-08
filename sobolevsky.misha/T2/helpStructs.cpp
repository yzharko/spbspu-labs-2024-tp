#include "helpStructs.hpp"
#include <iostream>

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::Delimitr_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (tolower(c) != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::Double_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> exp.key1_;
  return in;
}

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::Char_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> exp.key2_;
  return in;
}

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::String_ && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  getline(in, exp.key3_, '"');
  return in;
}
