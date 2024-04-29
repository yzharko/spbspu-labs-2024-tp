#include "DataStruct.hpp"
#include <iostream>
#include <iomanip>
#include "Delimeter.hpp"
#include "KeyStruct.hpp"
#include "StreamGuard.hpp"

namespace sukacheva {
  std::istream& operator>>(std::istream& is, DataStruct& val)
  {
    std::istream::sentry guard(is);
    if (!guard)
    {
      return is;
    }
    std::string key = "";
    DataStruct data;
    is >> Delimeter{ '(' } >> Delimeter{ ':' };
    for (int i = 1; i <= 3; i++)
    {
      is >> key;
      if (key == "key1")
      {
        is >> DblLit{ data.key1 } >> Delimeter{ ':' };
      }
      else if (key == "key2")
      {
        is >> SllLit{ data.key2 } >> Delimeter{ ':' };
      }
      else if (key == "key3")
      {
        is >> String{ data.key3 } >> Delimeter{ ':' };
      }
    }
    is >> Delimeter{ ')' };
    if (is)
    {
      val = data;
    }
    return is;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& val)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    StreamGuard StreamGuard(out);
    out << "(";
    out << ":key1 " << std::fixed << std::setprecision(1) << val.key1 << "d";
    out << ":key2 " << val.key2 << "ll";
    out << ":key3 \"" << val.key3 << "\":";
    out << ")";
    return out;
  }

  bool operator<(const DataStruct& left, const DataStruct& right)
  {
    if (left.key1 != right.key1)
    {
      return (left.key1 < right.key1);
    }
    else if (left.key2 != right.key2)
    {
      return (abs(left.key2) < abs(right.key2));
    }
    else
    {
      return (left.key3.length() < right.key3.length());
    }
  }
}
