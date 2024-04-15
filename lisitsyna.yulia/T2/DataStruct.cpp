#include "DataStruct.hpp"
#include "InputStructs.hpp"
#include "ScopeGuard.hpp"
#include <iomanip>

bool lisitsyna::operator<(const lisitsyna::Data& first, const lisitsyna::Data& second)
{
  if (first.key1 == second.key1)
  {
    if (first.key2 == second.key2)
      return first.key3 < second.key3;
    else
      return first.key2 < second.key2;
    }
  else
    return first.key1 < second.key1;
}

std::istream& lisitsyna::operator>>(std::istream& in, Data& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  lisitsyna::Data input;
  {
    using sep = Delimeter;
    using ll = LongLong;
    using chr = Char;
    using str = String;
    in >> sep{ '(' };
    in >> sep{ ':' };
    for (int i = 0; i < 3; i++)
    {
      std::string keyx = "";
      in >> keyx;
      if (keyx == "key1")
      {
        in >> ll{ input.key1 };
        in >> sep{ ':' };
      }
      else if (keyx == "key2")
      {
        in >> chr{ input.key2 };
        in >> sep{ ':' };
      }
      else if (keyx == "key3")
      {
        in >> str{ input.key3 };
        in >> sep{ ':' };
      }
    }
    in >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& lisitsyna::operator<<(std::ostream& out, const Data& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << src.key1 << "ll" << ":";
  out << "key2 " << '\'' << src.key2 << "\':";
  out << "key3 " << '\"' << src.key3 << '\"';
  out << ":)";
  return out;
}
