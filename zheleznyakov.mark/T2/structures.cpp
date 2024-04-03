#include "structures.hpp"

namespace zheleznyakov
{

  using sep = DelimiterIO;
  using label = LabelIO;
  using rl = RealIO;
  using dbl = DoubleIO;
  using str = StringIO;

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> DelimiterIO{'d'};
  }

  std::istream &operator>>(std::istream &in, RealIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> sep{'('} >> sep{':'} >> label{"N"};
    in >> dest.ref.first;
    in >> sep{':'} >> label{"D"};
    in >> dest.ref.second;
    in >> sep{':'} >> sep{')'};
    return in;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, LabelIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> data) && (data != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    std::string currentKey = "";
    in >> sep{'('};
    for (size_t i = 0; i < 3; i++)
    {
      in >> sep{':'} >> currentKey;
      if (currentKey == "key1")
      {
        in >> dbl{input.key1};
      }
      else if (currentKey == "key2")
      {
        in  >> rl{input.key2};
      }
      else if (currentKey == "key3")
      {
        in >> str{input.key3};
      }
    }
    in >> sep{':'} >> sep{')'};
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

  iofmtguard::iofmtguard(std::basic_ios<char> &s):
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}