#include "dataStruct.hpp"
#include "typesKeys.hpp"
#include "iofmtguard.hpp"
#include "delimiter.hpp"

namespace nikiforov
{
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
          in >> sep{ '\'' } >> chr{ input.key2 } >> sep{ '\'' };
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
}
