#include "DataStruct.hpp"
#include "ScopeGuard.hpp"
#include "pattern.hpp"
#include "Structure.hpp"

#include <iostream>

bool comp(const Data& rh, const Data& lf)
{
  if (rh.key1 != lf.key1)
  {
    return rh.key1 < lf.key1;
  }
  if (lf.key2 != rh.key2)
  {
    return rh.key2 < lh.key2;
  }
  return rh.key3.length() < lf.key3.length();
}

std::istream& operator>>(std::istream& in, Data& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Data input;
  {
    using sep = Delimiter;
    using label = Label;
    using sll = SllLit;
    using chr = ChrLit;
    using str = StringKey;
    in >> sep{ '(' };
    in >> sep{ ':' };

    for (int i = 0; i < 3; i++)
    {
      std::string keyx = "";
      in >> keyx;
      if (keyx == "key1")
      {
        in >> sll{ input.key1 };
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
    if (in)
    {
      dest = input;
    }
    return in;
  }
}

std::ostream& operator<<(std::ostream& out, const Data& src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard fmtguard(out);
  out << "(:";
  out << "key1 " << std::uppercase << src.key1 << ":";
  out << "key2 " << "\'" << src.key2 << "\'" << ":";
  out << "key3 " << '\"' << src.key3 << '\"';
  out << ":)";
  return out;
}
