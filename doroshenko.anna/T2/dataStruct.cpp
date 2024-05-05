#include "dataStruct.hpp"
#include "structures.hpp"
#include "scopeGuard.hpp"

std::istream& doroshenko::operator>>(std::istream& input, DataStruct& dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  DataStruct structure;
  {
    using separator = DelimiterIO;
    using dbl = DoubleIO;
    using chr = CharIO;
    using str = StringIO;
    std::string key;
    input >> separator{ '(' };
    for (int i = 0; i < 3; i++)
    {
      input >> separator{ ':' } >> key;
      if (key == "key1")
      {
        input >> dbl{ structure.key1 };
      }
      else if (key == "key2")
      {
        input >> chr{ structure.key2 };
      }
      else if (key == "key3")
      {
        input >> str{ structure.key3 };
      }
      else
      {
        input.setstate(std::ios::failbit);
      }
    }
    input >> separator{ ':' } >> separator{ ')' };
  }
  if (input)
  {
    dest = structure;
  }
  return input;
}

std::ostream& doroshenko::operator<<(std::ostream& output, const DataStruct& src)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  iofmtguard fmtguard(output);
  output << "(:key1 ";
  outDblSci(output, src.key1);
  output << ":key2 " << "'" << src.key2 << "'";
  output << ":key3 " << '"' << src.key3 << '"' << ":)";
  return output;
}

bool doroshenko::compareStructs(const DataStruct& firstStruct, const DataStruct& secondStruct)
{
  if (firstStruct.key1 == secondStruct.key1)
  {
    if (firstStruct.key2 == secondStruct.key2)
    {
      return (firstStruct.key3.length() < secondStruct.key3.length());
    }
    else
    {
      return (firstStruct.key2 < secondStruct.key2);
    }
  }
  else
  {
    return (firstStruct.key1 < secondStruct.key1);
  }
}
