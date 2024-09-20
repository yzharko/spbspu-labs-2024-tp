#include "delimiters.hpp"

std::istream& malanin::operator>>(std::istream& is, malanin::DelimiterIO&& exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& malanin::operator>>(std::istream& is, malanin::LabelIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  std::string data = "";
  is >> data;
  bool cmp = data != value.exp;
  if (is and cmp)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& malanin::operator>>(std::istream& is, malanin::KeyIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> value.ref;
  if (value.ref != "key1" and value.ref != "key2" and value.ref != "key3")
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}
