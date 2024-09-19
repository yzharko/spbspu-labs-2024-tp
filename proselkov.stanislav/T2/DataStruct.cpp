#include "DataStruct.hpp"

namespace proselkov
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != std::tolower(dest.exp)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, SllLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, UllLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    return in;
  }
  std::istream& operator>>(std::istream& in, DelStrIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t i = 0;
    while (dest.exp[i] != '\0')
    {
      in >> DelimiterIO({ dest.exp[i++] });
    }
    return in;
  }
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using sepStr = DelStrIO;
      using sllLit = SllLitIO;
      using ullLit = UllLitIO;
      using str = StringIO;
      in >> sepStr({ "(:" });
      int keyNumber = 0;
      for (size_t i = 0; i < 3; i++) {
        in >> sepStr({ "key" }) >> keyNumber;
        if (keyNumber == 1)
        {
          in >> sllLit{ input.key1 };
        }
        else if (keyNumber == 2)
        {
          in >> ullLit{ input.key2 };
        }
        else if (keyNumber == 3)
        {
          in >> str{ input.key3 };
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
        in >> sep{ ':' };
      }
      in >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }
  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 " << src.key1 << "ll";
    out << ":key2 " << src.key2 << "ull";
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
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
