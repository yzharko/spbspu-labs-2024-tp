#include <iostream>
#include "datastruct.hpp"

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
