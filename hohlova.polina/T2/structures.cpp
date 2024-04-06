#include "structures.hpp"
#include "iofmtguard.hpp"

namespace hohlova
{
  using sep = DelimiterIO;
  using label = LabelIO;
  using str = StringIO;

  std::istream& operator>>(std::istream& in, SLLLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    long long temp;
    in >> temp;
    dest.ref = temp;
    return in;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
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
  bool operator<(const std::pair<long long, unsigned long long>& left, const std::pair<long long, unsigned long long>& right)
  {
    const double val1 = static_cast<double>(left.first) / left.second;
    const double val2 = static_cast<double>(right.first) / right.second;
    return val1 < val2;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
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
        in >> SLLLitIO{ input.key1 };
      }
      else if (currentKey == "key2")
      {
        std::string key2_str;
        in >> key2_str;
        size_t colon_pos = key2_str.find(':');
        if (colon_pos != std::string::npos)
        {
          std::string ll_part_str = key2_str.substr(0, colon_pos);
          std::string ull_part_str = key2_str.substr(colon_pos + 1);
          long long ll_part = std::stoll(ll_part_str);
          unsigned long long ull_part = std::stoull(ull_part_str);
          input.key2 = std::make_pair(ll_part, ull_part);
        }
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
}
