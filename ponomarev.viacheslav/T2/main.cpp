#include <iomanip>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>

namespace ponomarev
{
  // формат ввода:
  // (:key1 5.45e-2:key2 0b1000101:key3 "Data":)
  struct Data
  {
    double key1;
    std::string key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double &ref;
  };

  struct LongLongIO
  {
    std::string &ref;
  };

  struct StringIO
  {
    std::string &ref;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DoubleIO &&dest);
  std::istream &operator>>(std::istream &in, LongLongIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, Data &dest);
  std::ostream &operator<<(std::ostream &out, const Data &dest);
}

bool compare_entry(const ponomarev::Data &e1, const ponomarev::Data &e2)
{
  if (e1.key1 != e2.key1)
  {
    return (e1.key1 < e2.key1);
  }
  else if (e1.key2 != e2.key2)
  {
    return (std::stoull(e1.key2) < std::stoull(e2.key2));
  }
  return (e1.key3.length() < e2.key3.length());
};

int main()
{
  using ponomarev::Data;
  std::vector< Data > data;
  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< Data >(std::cin),
      std::istream_iterator< Data >(),
      std::back_inserter(data)
    );
    if (std::cin.fail() && !std::cin.eof())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  std::sort(data.begin(), data.end(), compare_entry);
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );

  return 0;
}

namespace ponomarev
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (tolower(c) != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, LongLongIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::getline(in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' }, dest.ref, ':');
    return in;
  }

  std::istream &operator>>(std::istream &in, DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream &operator>>(std::istream &in, Data &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Data input;
    {
      using sep = DelimiterIO;
      using dbl = DoubleIO;
      using lolo = LongLongIO;
      using str = StringIO;
      std::string typeOfKey;
      in >> sep{ '(' };
      for (size_t i = 0; i < 3; i++)
      {
        if (typeOfKey == "key2")
        {
          std::getline(in , typeOfKey, ' ');
        }
        else
        {
          std::getline(in >> DelimiterIO{ ':' }, typeOfKey, ' ');
        }

        if (typeOfKey == "key1")
        {
          in >> dbl{ input.key1 };
        }
        else if (typeOfKey == "key2")
        {
          in >> lolo{ input.key2 };
        }
        else if (typeOfKey == "key3")
        {
          in >> str{ input.key3 };
        }
        else
        {
          in.setstate(std::ios::failbit);
          break;
        }
      }

      if (typeOfKey == "key2")
      {
        in >> sep{ ')' };
      }
      else
      {
        in >> sep{ ':' };
        in >> sep{ ')' };
      }
    }

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
    double mantis = src.key1;
    int degree = 0;
    out << "(:";
    if (mantis < 10)
    {
      while (mantis < 1)
      {
        mantis *= 10;
        degree += 1;
      }
      out << "key1 "<< std::fixed << std::setprecision(1) << mantis << "e-" << degree << ":";
    }
    else
    {
      while (mantis > 9)
      {
        mantis /= 10;
        degree += 1;
      }
      out << "key1 "<< std::fixed << std::setprecision(1) << mantis << "e+" << degree << ":";
    }
    out << "key2 " << "0b" << src.key2 << ":";
    out << "key3 " << '"' << src.key3 << '"';
    out << ":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
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
