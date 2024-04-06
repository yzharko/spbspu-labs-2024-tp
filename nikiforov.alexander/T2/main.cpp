#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>

namespace nikiforov
{
  struct Data
  {
    unsigned long long key1;
    char key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct UnsignedLongLongIO
  {
    unsigned long long& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char >& s) noexcept;
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
  bool operator<(const Data& first, const Data& second) noexcept;
}

int main()
{
  using structData = nikiforov::Data;

  std::vector< structData > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< structData >(std::cin),
      std::istream_iterator< structData >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< structData >(std::cout, "\n")
  );

  return 0;
}

namespace nikiforov
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
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, CharIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
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

  std::istream& operator>>(std::istream& in, Data& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    {
      using sep = DelimiterIO;
      using ull = UnsignedLongLongIO;
      using chr = CharIO;
      using str = StringIO;
      std::string key = "";
      const size_t countKeys = 3;

      in >> sep{ '(' };
      for (size_t i = 0; i < countKeys; i++)
      {
        in >> sep{ ':' } >> key;
        if (key == "key1")
        {
          in >> sep{ '0' } >> ull{ input.key1 };
        }
        else if (key == "key2")
        {
          in >> sep{ '\'' } >> chr{input.key2} >> sep{ '\'' };
        }
        else if (key == "key3")
        {
          in >> str{ input.key3 };
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{ ':' } >> sep{ ')' };
    }
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
    out << "key1 " << "0" << src.key1 << ":";
    out << "key2 " << "'" << src.key2 << "'" << ":";
    out << "key3 " << std::quoted(src.key3) << ":";
    out << ")";
    return out;
  }

  bool operator<(const Data& first, const Data& second) noexcept
  {
    if (first.key1 != second.key1)
    {
      return first.key1 < second.key1;
    }
    else if (first.key2 != second.key2)
    {
      return first.key2 < second.key2;
    }
    else
    {
      return first.key3.size() < second.key3.size();
    }
  }

  iofmtguard::iofmtguard(std::basic_ios< char >& s) noexcept :
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
