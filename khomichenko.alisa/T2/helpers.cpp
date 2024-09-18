#include <iomanip>
#include <iostream>
#include <string>
#include "helpers.hpp"

namespace khomichenko
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    if(!(in >> dest.ref) || dest.ref == 0)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }


  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, SllIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    if (!(in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' }))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::ostream& sciDouble (std::ostream& out, double num)
  {
    int degree = 0;
    std::string tail;
    if (num >= 1.0)
    {
      while (num > 1.0)
      {
        num /= 10;
        degree += 1;
      }
      tail += "+";
    }
    else
    {
      while (num < 1.0)
      {
        num *= 10;
        degree += 1;
      }
      tail = "-";
    }
    out << num << "e" << tail << degree;
    return out;
  }
}
