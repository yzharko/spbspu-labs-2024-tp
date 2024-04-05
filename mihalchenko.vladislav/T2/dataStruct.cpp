#include "dataStruct.hpp"
// #include <iostream>
// #include "delimiters.hpp"
#include "scopeguard.hpp"

std::istream &mihalchenko::operator>>(std::istream &is, DataStruct &value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  DataStruct inputDS;
  {
    using sep = DelimiterIO;
    using ull2 = UllBinIO;
    using complex = ComplexIO;
    using str = StringIO;
    bool flag11 = false;
    is >> sep{'('};
    std::string key = "";
    int c = 0;
    for (size_t i = 0; i < 3; i++)
    {
      c = i;
      if (flag11 == true)
      {
        flag11 = false;
      }
      else
      {
        is >> sep{':'};
      }
      is >> key;
      if (key == "key1")
      {
        is >> ull2{inputDS.key1_};
        flag11 = true;
      }
      else if (key == "key2")
      {
        is >> complex{inputDS.key2_};
      }
      else if (key == "key3")
      {
        is >> str{inputDS.key3_};
      }
      else
      {
        is.setstate(std::ios::failbit);
      }
    }
    if (key == "key1" && c == 2)
    {
      is >> sep{')'};
    }
    else
    {
      is >> sep{':'} >> sep{')'};
    }
  }
  if (is)
  {
    value = inputDS;
  }
  return is;
}

std::ostream &mihalchenko::operator<<(std::ostream &out, const DataStruct &value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "("
      << ":key1 "
      << "0b" << value.key1_ << ":key2 #c(" << std::fixed << std::setprecision(1)
      << value.key2_.real() << " " << value.key2_.imag() << ")"
      << ":key3 \"" << value.key3_ << "\":"
      << ")";
  return out;
}

bool mihalchenko::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1_ != rhs.key1_)
  {
    if (lhs.key1_ < rhs.key1_)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (abs(lhs.key2_) != abs(rhs.key2_))
  {
    if (abs(lhs.key2_) < abs(rhs.key2_))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    if (lhs.key3_.size() < rhs.key3_.size())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
