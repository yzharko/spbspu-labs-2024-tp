#include "yaDataStruct.hpp"
#include "delimiter.hpp"
#include "iofmtguard.hpp"
#include "types.hpp"

namespace hohlova
{
  using ull = ULLIO;
  using str = StringIO;
  using sep = DelimiterIO;
  using label = LabelIO;
  using comp = ComplexIO;

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
    for (size_t j = 0; j < 3; j++)
    {
      in >> sep{ ':' } >> currentKey;
      if (currentKey == "key1")
      {
        in >> ull{ input.key1 };
      }
      else if (currentKey == "key2")
      {
        in >> comp{ input.key2 };
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
    out << "key1 0x" << std::uppercase << std::hex << src.key1;
    out << ":";
    out << "key2 "
      << "#c(" << std::fixed << std::setprecision(1) << src.key2.real() << " "<< src.key2.imag() << ")";
    out << ":";
    out << "key3 \"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool operator<(const Data& lhs, const Data& rhs)
  {
    return (lhs.key1 < rhs.key1 || abs(lhs.key2) < abs(rhs.key2) || lhs.key3.size() < rhs.key3.size());
  }
}
