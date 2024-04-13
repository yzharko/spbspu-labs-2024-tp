#include "dataStruct.hpp"
#include "delimiters.hpp"
#include "scopeGuard.hpp"

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
    bool flKey1 = false;
    is >> sep{'('};
    std::string key = "";
    int c = 0;
    for (size_t i = 0; i < 3; i++)
    {
      c = i;
      if (flKey1 != true)
      {
        is >> sep{':'};
      }
      is >> key;
      if (key == "key1")
      {
        is >> ull2{inputDS.key1_};
        flKey1 = true;
      }
      else if (key == "key2")
      {
        is >> complex{inputDS.key2_};
        flKey1 = false;
      }
      else if (key == "key3")
      {
        is >> str{inputDS.key3_};
        flKey1 = false;
      }
      else
      {
        is.setstate(std::ios::failbit);
      }
    }
    (key == "key1" && c == 2) ? (is >> sep{')'}) : is >> sep{':'} >> sep{')'};
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
  out << "(:key1 0b" << value.key1_ << ":key2 #c(" << std::fixed << std::setprecision(1)
      << value.key2_.real() << " " << value.key2_.imag() << "):key3 \"" << value.key3_ << "\":)";
  return out;
}

bool mihalchenko::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1_ != rhs.key1_)
  {
    return (lhs.key1_ < rhs.key1_);
  }
  else if (abs(lhs.key2_) != abs(rhs.key2_))
  {
    return (abs(lhs.key2_) < abs(rhs.key2_));
  }
  else
  {
    return (lhs.key3_.size() < rhs.key3_.size());
  }
}
