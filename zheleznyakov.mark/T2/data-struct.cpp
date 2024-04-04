#include "iofmtguard.hpp"
#include "data-struct.hpp"
#include "separators.hpp"

namespace zheleznyakov
{
  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    std::string currentKey = "";
    in >> SeparatorIO{'('};
    for (size_t i = 0; i < 3; i++)
    {
      in >> SeparatorIO{':'} >> currentKey;
      if (currentKey == "key1")
      {
        in >> DoubleIO{input.key1};
      }
      else if (currentKey == "key2")
      {
        in >> RealIO{input.key2};
      }
      else if (currentKey == "key3")
      {
        in >> StringIO{input.key3};
      }
    }
    in >> SeparatorIO{':'} >> SeparatorIO{')'};
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream &operator<<(std::ostream &out, const Data &src)
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

  bool operator<(const Data &left, const Data &right)
  {
    return (left.key1 < right.key1 || left.key2 < right.key2 || left.key3.size() < right.key3.size());
  }
}
