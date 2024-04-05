#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace nspace
{
  // формат ввода:
  // { "key1": 1.0d, "key2": "Let madness release you" }
  struct Data
  {
    double key1;
    char key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  // scope guard дл€ возврата состо€ни€ потока в первоначальное состо€ние
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, Data& dest);
  std::ostream& operator<<(std::ostream& out, const Data& dest);
}

int main()
{
  using nspace::Data;

  std::vector< Data > data;
  std::istringstream iss("(:key1 00:key2 'a':key3 \"Let madness release you\":)");

  std::copy(
    std::istream_iterator< Data >(iss),
    std::istream_iterator< Data >(),
    std::back_inserter(data)
  );

  std::cout << "Data:\n";
  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< Data >(std::cout, "\n")
  );

  return 0;
}

namespace nspace
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    // все перегрузки операторов ввода/вывода должны начинатьс€ с проверки экземпл€ра класса sentry
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

  std::istream& operator>>(std::istream& in, DoubleIO&& dest)
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

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> StringIO{ data }) && (data != dest.exp))
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
    {
      using sep = DelimiterIO;
      using label = LabelIO;
      using dbl = DoubleIO;
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
          in >> dbl{ input.key1 };
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
      /*
      in >> sep{ '(' };
      in >> label{ "key1" } >> sep{ ':' } >> dbl{ input.key1 };
      in >> sep{ ',' };
      in >> label{ "key2" } >> sep{ ':' } >> str{ input.key2 };
      in >> sep{ ')' };*/
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
    out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d" << ":";
    out << "key2 " << "'" << src.key2 << "'" << ":";
    out << "key3 " << src.key3 << ":";
    out << ")";
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