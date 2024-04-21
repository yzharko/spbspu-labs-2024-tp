#include "io_structures.hpp"
#include <iostream>

std::istream & kovshikov::operator>>(std::istream & is, DelimiterIO && value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != value.exp)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & kovshikov::operator>>(std::istream & is, CharIO && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return is >> DelimiterIO{'\''} >> value.ch >> DelimiterIO{'\''};
}

std::istream & kovshikov::operator>>(std::istream & is, PairIO && value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  is >> Del{'('} >> Del{':'} >> Del{'N'};
  is >> value.pair.first;
  is  >> Del{':'} >> Del{'D'};
  is >> value.pair.second;
  is >> Del{':'} >> Del{')'};
  return is;
}

std::istream & kovshikov::operator>>(std::istream & is, StringIO && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(is >> DelimiterIO{ '"' }, value.str, '"');
}
