#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "structuresOfKeys.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream &ponomarev::operator>>(std::istream &in, yaDataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  yaDataStruct input;
  {
    using sep = DelimiterIO;
    using dbl = DoubleIO;
    using lolo = LongLongIO;
    using str = StringIO;
    using pair = PairIO;
    std::string typeOfKey = "key3";
    in >> sep{ '(' };

    for (size_t i = 0; i < 3; i++)
    {
      if (typeOfKey == "key3" || typeOfKey == "key2")
      {
        std::getline(in >> sep{ ':' }, typeOfKey, ' ');
      }
      else
      {
        std::getline(in , typeOfKey, ' ');
      }

      if (typeOfKey == "key1")
      {
        in >> lolo{ input.key2 };
      }
      else if (typeOfKey == "key2")
      {
        in >> pair{ input.key4 };
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

    if ((typeOfKey == "key3"))
    {
      in >> sep{ ':' };
      in >> sep{ ')' };
    }
    else
    {
      in >> sep{ ')' };
    }
  }

  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream &ponomarev::operator<<(std::ostream &out, const yaDataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);

  out << "(:";
  out << "key1 " << "0b" << src.key2 << ":";
  out << "key2 (:N " << src.key4.first << ":D " << src.key4.second << ":):";
  out << "key3 " << '"' << src.key3 << '"';
  out << ":)";
  return out;
}

bool ponomarev::operator<(const yaDataStruct & left, const yaDataStruct & right)
{
  if (left.key2 != right.key2)
  {
    return (std::stoll(left.key2) < std::stoll(right.key2));
  }
  else if (left.key4 != right.key4)
  {
    return (left.key2 < right.key2);
  }
  return (left.key3.length() < right.key3.length());
}
