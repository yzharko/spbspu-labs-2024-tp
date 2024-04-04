#include "datastruct.hpp"
#include "delimeter.hpp"
#include "structs.hpp"
#include "iofmtguard.hpp"
#include "iomanip"

namespace taskaev
{
  std::istream& operator>>(std::istream& is, DataStruct& dest)
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
      std::string keyx = "";
      is >> del{ '(' } >> del{ ':' };
      int countKey = 0;
      while(countKey != 3)
      {
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

  std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 0x" << std::uppercase << std::hex << dest.key1;
    out << ":key2 " << "#c(" << dest.key2.real() << " " << dest.key2.imag() << ")";
    out << ":key3 \"" << dest.key3 << '\"';
    out << ":)";
    return out;
  }

  bool operator<(const DataStruct& left, const DataStruct& right)
  {
    if(left.key1 != right.key1)
    {
      return left.key1 < right.key1;
    }
    if(left.key2 != right.key2)
    {
      return abs(left.key2) < abs(right.key2);
    }
    return left.key3 < right.key3;
  }
}
