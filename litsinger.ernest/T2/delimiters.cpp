#include "delimiters.hpp"

std::istream& litsinger::operator>>(std::istream& is, litsinger::DelimiterIO&& exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (static_cast<char> (tolower(c)) != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}


std::istream& litsinger::operator>>(std::istream& is, litsinger::LabelIO&& value)
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

std::istream& litsinger::operator>>(std::istream& is, litsinger::KeyIO&& value)
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
