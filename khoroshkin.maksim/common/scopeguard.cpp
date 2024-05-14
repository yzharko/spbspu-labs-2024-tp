#include "scopeguard.hpp"

khoroshkin::iofmtguard::iofmtguard(std::basic_ios< char > & s) :
  s_(s), fill_(s.fill()), precision_(s.precision()), fmt_(s.flags())
{}

khoroshkin::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
