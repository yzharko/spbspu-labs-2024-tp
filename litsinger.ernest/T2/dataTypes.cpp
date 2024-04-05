#include <iostream>
#include "dataTypes.hpp"
#include "delimiters.hpp"

std::istream& litsinger::operator>>(std::istream& is, litsinger::HexULongLongIO&& value)
{
  using del = litsinger::DelimiterIO;
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> del{'0'} >> del{'x'} >> std::hex >> value.ref;
  return is;
}
std::istream& litsinger::operator>>(std::istream& is, litsinger::BinULongLongIO&& value)
{
  using del = litsinger::DelimiterIO;
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(&: is >> del{ .expected: '0' } >> del{ .expected: 'b' }, &: value.ref, delim : ':');
}


std::istream& litsinger::operator>>(std::istream& is, litsinger::StringIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(is >> litsinger::DelimiterIO{'"'}, value.ref, '"');
}
