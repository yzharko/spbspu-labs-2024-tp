#include "dataStruct.hpp"
#include "iofmtguard.hpp"
#include "delimiter.hpp"
#include "types.hpp"

namespace hohlova
{
  using sep = DelimiterIO;
  using rl = RealIO;
  using dbl = DoubleIO;
  using str = StringIO;

  std::istream& operator>>(std::istream& in, Data& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    std::string currentKey = "";
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++)
    {
      in >> sep{ ':' } >> currentKey;
      if (currentKey == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (currentKey == "key2")
      {
        in >> rl{ input.key2 };
      }
      else if (currentKey == "key3")
      {
        in >> str{ input.key3 };
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Data& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":";
    out << "key2 "
      << "(:N " << src.key2.first << ":D " << src.key2.second << ":)";
    out << ":";
    out << "key3 \"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool operator<(const Data& left, const Data& right)
  {
    return (left.key1 < right.key1 || left.key2 < right.key2 || left.key3.size() < right.key3.size());
  }

  bool operator<(const std::pair<sll, ull>& leftReal, const std::pair<sll, ull>& rightReal)
  {
    const double val1 = static_cast<double>(leftReal.first) / leftReal.second;
    const double val2 = static_cast<double>(rightReal.first) / rightReal.second;
    return val1 < val2;
  }
}
