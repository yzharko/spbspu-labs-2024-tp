#include "dataStruct.hpp"
#include "taskTypes.hpp"
#include "delim.hpp"
#include "scopeGuard.hpp"

using delim = psarev::DelimiterIO;
std::istream& psarev::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct houseKeeper;
  {
    in >> delim{ '(' };
    std::string keyNum;
    for (size_t i = 0; i < 3 && in; ++i)
    {
      in >> delim{ ':' } >> keyNum;
      if (keyNum == "key1")
      {
        in >> DoubleIO{ houseKeeper.key1 };
      }
      else if (keyNum == "key2")
      {
        in >> UllHexIO{ houseKeeper.key2 };
      }
      else if (keyNum == "key3")
      {
        in >> StringIO{ houseKeeper.key3 };
      }
    }
    in >> delim{ ':' } >> delim{ ')' };
  }
  if (in)
  {
    data = houseKeeper;
  }
  return in;
}

std::ostream& psarev::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << std::fixed << std::setprecision(1) << data.key1 << "d";
  out << ":key2 0x" << data.key2;
  out << ":key3 " << std::quoted(data.key3) << ":)";
  return out;
}

bool psarev::operator<(const DataStruct& first, const DataStruct& second)
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
