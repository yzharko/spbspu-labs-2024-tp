#include <iostream>
#include "datastruct.hpp"

iofmtguard::iofmtguard(std::basic_ios< char > &s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

std::istream& operator >> (std::istream& is, DataStruct& dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  DataStruct data;
  {
    using del = DelimeterI;
    using hex = unsignedLongLongI;
    using com = complexI;
    using str = stringI;
    is >> del{ '(' } >> del{ ':' };
    int countKey = 0;
    while(countKey != 3)
    {
      std::string keyx = "";
      is >> keyx;
      if (keyx == "key1")
      {
        is >> hex{data.key1};
        is >> del{ ':' };
      }
      else if( keyx == "key2")
      {
        is >> com{data.key2};
        is >> del{ ':' };
      }
      else if (keyx == "key3")
      {
        is >> str{data.key3};
        is >> del{ ':' };
      }
      countKey++;

    }
    is >> del{ ')' };
    if (is)
    {
      dest = data;
    }

    return is;
  }
}

std::ostream& operator << (std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  return out;
}
