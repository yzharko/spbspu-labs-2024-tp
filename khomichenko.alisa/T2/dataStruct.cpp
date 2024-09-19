#include "dataStruct.hpp"
#include "helpers.hpp"
#include "scopeGuard.hpp"
#include <iomanip>
#include <iostream>
namespace khomichenko
{
  std::istream &operator>>(std::istream &in, DataStruct &dataStr)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Guard guard(in);

    DataStruct data;
    std::string key;

    in >> DelimiterIO{ '(' };
    for (int i =  0; i < 3; i++)
    {
      in >> DelimiterIO{ ':' } >> key;
      if (key == "key1")
      {
        in >> DoubleIO{data.key1};
      }
      else if (key == "key2")
      {
        in >> SllIO{ data.key2 };
      }
      else if (key == "key3")
      {
        in >> StringIO{ data.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> DelimiterIO{ ':' } >> DelimiterIO { ')' };
    if (in)
    {
      dataStr = data;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &dataStr)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    out << "(:key1 " << std::fixed << std::setprecision(1);
    sciDouble(out, dataStr.key1);
    out << ":key2 " << dataStr.key2 << "ll:key3 " << "\"" << dataStr.key3 << "\":)";
    return out;
  }

  bool operator>(const DataStruct &first, const  DataStruct &second)
  {
    if (first.key1 != second.key1)
    {
      return first.key1 > second.key1;
    }
    else if (first.key2 != second.key2)
    {
      return first.key2 > second.key2;
    }
    else if (first.key3.length() != second.key3.length())
    {
      return first.key3.length() > second.key3.length();
    }
    else
    {
      return 0;
    }
  }

  bool operator<(const DataStruct &first, const  DataStruct &second)
  {
    return !(first > second);
  }
}
