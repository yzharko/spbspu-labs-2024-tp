#include "inDelim.hpp"

#include <iostream>
#include <string>

#include "delimiter.hpp"
#include "guard.hpp"


std::istream &anikanov::operator>>(std::istream &in, DelimiterIO &&dest)
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
