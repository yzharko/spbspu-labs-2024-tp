#include "dataStruct.hpp"
#include "structData.hpp"
#include "delimeter.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream & popov::operator>>(std::istream & is, popov::DataStruct & number)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  popov::DataStruct input;
  using del = popov::DelimiterIO;
  using dob = popov::DoubleIO;
  using ull = popov::UnsLongLongIO;
  using str = popov::StringIO;
  std::string key = "";
  is >> del{'('};
  for (int i = 0; i < 3; ++i)
  {
    is >> del{':'} >> key;
    if (key == "key1")
    {
      is >> dob{input.key1};
    }
    else if (key == "key2")
    {
      is >> ull{input.key2};
    }
    else if (key == "key3")
    {
      is >> str{input.key3};
    }
  }
  is >> del{':'} >> del{')'};
  number = input;
  return is;
}

std::ostream & popov::operator<<(std::ostream & out, const DataStruct & struc)
  {
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  int count = 0;
  double value = struc.key1;
  if (value > 10)
  {
    while (value > 10)
    {
      value = value / 10;
      count += 1;
    }
    out << "key1 " << std::fixed << std::setprecision(1) << value << "e+" << count;
  }
  else
  {
    if (value < 1)
    {
      while (value < 1)
      {
        value = value * 10;
        count += 1;
      }
      out << "key1 " << std::fixed << std::setprecision(1) << value << "e-" << count;
    }
  }
  out << ":key2 " << struc.key2 << "ull";
  out << ":key3 \"" << struc.key3 << "\":)";
  return out;
}

bool popov::operator<(const DataStruct & lhs, const DataStruct & rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}
