#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "structuresOfKeys.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream &ponomarev::operator>>(std::istream &in, Data &dest)
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

std::ostream &ponomarev::operator<<(std::ostream &out, const Data &src)
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

bool ponomarev::operator<(const ponomarev::Data & left, const ponomarev::Data & right)
{
  if (left.key1 != right.key1)
  {
    return (left.key1 < right.key1);
  }
  else if (left.key2 != right.key2)
  {
    return (std::stoull(left.key2) < std::stoull(right.key2));
  }
  return (left.key3.length() < right.key3.length());
}
