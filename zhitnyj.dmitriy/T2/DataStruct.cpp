#include "DataStruct.h"
#include <sstream>
#include <iomanip>

std::istream& operator>>(std::istream& is, DataStruct& ds)
{
  bool k1 = 0;
  bool k2 = 0;

  std::string line;
  if (!getline(is, line, ')')) return is;

  std::istringstream lineStream(line.substr(1));
  std::string part;
  while (getline(lineStream >> std::ws, part, ':'))
  {
    auto pos = part.find(' ');
    if (pos == std::string::npos) continue;
    std::string key = part.substr(0, pos);
    std::string value = part.substr(pos + 1);

    if (value.find("ull") != std::string::npos)
    {
      k1 = true;
      ds.key1 = std::stoull(value.substr(0, value.find("ull")));
    }
    else if (value.find("0x") != std::string::npos || value.find("0X") != std::string::npos)
    {
      k2 = true;
      ds.key2 = std::stoull(value, nullptr, 16);
    }
    else
    {
      ds.key3 = "\"" + value.substr(1, value.length() - 2);
    }
  }

  if (!k1 || !k2)
  {
    ds.key3 = "";
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
{
  if (ds.key3.empty())
  {
    return os;
  }

  os << "(:key1 ";

  os << ds.key1 << "ull:key2 ";

  os << "0x" << std::hex << ds.key2 << ":key3 " << std::dec;

  os << ds.key3 << "\":)";

  return os;
}
