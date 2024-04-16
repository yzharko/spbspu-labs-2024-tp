#include "DataStruct.hpp"
#include <string>
#include <iostream>
#include "InpOutTypes.hpp"
#include "Iofmtguard.hpp"

std::istream& zasulsky::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double key1 = 0.0;
  long long key2 = 0;
  std::string key3 = "";
  bool isK1 = false;
  bool isK2 = false;
  bool isK3 = false;
  int num = 0;
  in >> DelimiterIO{ '(' };
  while (!(isK1 && isK2 && isK3) && in.good())
  {
    in >> LabelIO{ ":key" } >> num;
    if (num == 1 && !isK1)
    {
      in >> DblI{ key1 };
      isK1 = true;
    }
    else if (num == 2 && !isK2)
    {
      in >> SllIO{ key2 };
      isK2 = true;
    }
    else if (num == 3 && !isK3)
    {
      in >> StringIO{ key3 };
      isK3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> LabelIO{ ":)" };
  if (in)
  {
    dest = DataStruct{ key1, key2, key3 };
  }
  return in;
}
std::ostream& zasulsky::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard guard(out);
  out << "(";
  out << ":key1 " << DblO{ data.key1 };
  out << ":key2 " << data.key2 << "ll";
  out << ":key3 " << '"' << data.key3 << '"';
  out << ":)";
  return out;
}
bool zasulsky::compare(zasulsky::DataStruct& lhs, zasulsky::DataStruct& rhs)
{
  if (rhs.key1 > lhs.key1)
  {
    return 1;
  }
  else if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 == rhs.key2)
    {
      return rhs.key3.length() > lhs.key3.length();
    }
    return rhs.key2 > lhs.key2;
  }
  else
  {
    return 0;
  }
}
