#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "structuresOfKeys.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream &ponomarev::operator>>(std::istream &in, DataStruct &dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct input;
  {
    using sep = DelimiterIO;
    using dbl = DoubleIO;
    using lolo = LongLongIO;
    using str = StringIO;
    std::string typeOfKey = "key3";
    in >> sep{ '(' };

    for (size_t i = 0; i < 3; i++)
    {
      if (typeOfKey == "key3")
      {
        std::getline(in >> DelimiterIO{ ':' }, typeOfKey, ' ');
      }
      else
      {
        std::getline(in , typeOfKey, ' ');
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

std::ostream &ponomarev::operator<<(std::ostream &out, const DataStruct &src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);

  out << "(:";
  out << "key1 " << src.key1 << ":";
  out << "key2 " << "0b" << src.key2 << ":";
  out << "key3 " << '"' << src.key3 << '"';
  out << ":)";
  return out;
}

bool ponomarev::operator<(const DataStruct & left, const DataStruct & right)
{
  if (left.key1 != right.key1)
  {
    return (std::stod(left.key1) < std::stod(right.key1));
  }
  else if (left.key2 != right.key2)
  {
    return (std::stoull(left.key2) < std::stoull(right.key2));
  }
  return (left.key3.length() < right.key3.length());
}
