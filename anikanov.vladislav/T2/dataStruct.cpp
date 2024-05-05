#include "dataStruct.hpp"
#include <iostream>

std::istream &anikanov::operator>>(std::istream &in, anikanov::DelimiterIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (std::tolower(c) != std::tolower(dest.exp))) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const anikanov::DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  anikanov::iofmtguard fmtguard(out);
  out << "(:key1 " << src.key1 << "ull";
  out << ":key2 0" << std::oct << src.key2;
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}

anikanov::iofmtguard::iofmtguard(std::basic_ios< char > &s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
{
}

anikanov::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
