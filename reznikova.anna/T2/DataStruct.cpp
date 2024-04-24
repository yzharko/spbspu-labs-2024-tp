#include "DataStruct.hpp"
#include <iostream>
#include <iomanip>
#include "Delimeter.hpp"
#include "Keys.hpp"
#include "ScopeGuard.hpp"

bool reznikova::operator<(const reznikova::DataStruct & first, const reznikova::DataStruct & second)
{
  if (first.key1 != second.key1)
  {
    return (first.key1 < second.key1);
  }
  else if (first.key2 != second.key2)
  {
    return (abs(first.key2) < abs(second.key2));
  }
  else
  {
    return (first.key3.length() < second.key3.length());
  }
}

std::istream & reznikova::operator>>(std::istream & is, reznikova::DataStruct & value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  std::string key = "";
  DataStruct data_struct;
  is >> del{'('} >> del{':'};
  for (size_t i = 1; i <= 3; i++)
  {
    is >> key;
    if (key == "key1")
    {
      is >> ULLOCT{data_struct.key1} >> del{':'};
    }
    else if (key == "key2")
    {
      is >> CMPLSP{data_struct.key2} >> del{':'};
    }
    else
    {
      is >> STR{data_struct.key3} >> del{':'};
    }
  }
  is >> del{')'};
  if (is)
  {
    value = data_struct;
  }
  return is;
}

std::ostream & reznikova::operator<<(std::ostream & out, reznikova::DataStruct & value)
{
  std::ostream::sentry sentry(out);
  if(!sentry)
  {
    return out;
  }
  iofmtguard guard(out);
  out << "(:" << "key1" << ULLOCT{ value.key1 };
  out << ":" << "key2 #c(" << std::fixed << std::setprecision(1) << value.key2.real();
  out << " " << value.key2.imag() << ")";
  out << ":" << "key3 \"" << std::fixed << value.key3 << "\":)";
  return out;
}
