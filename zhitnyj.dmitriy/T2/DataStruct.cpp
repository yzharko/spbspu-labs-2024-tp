#include <string>
#include "DataStruct.h"

bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1) return key1 < other.key1;
  if (key2 != other.key2) return key2 < other.key2;
  return key3.length() < other.key3.length();
}

std::istream& operator>>(std::istream& is, DataStruct& ds)
{
  bool key1 = false;
  bool key2 = false;

  char ch;
  if (is >> ch && ch == '(')
  {
    std::string line;
    getline(is, line, ')');

    size_t start = 0;
    size_t end = line.find(':');
    while (end != std::string::npos)
    {
      std::string part = line.substr(start, end - start);
      size_t pos = part.find(' ');
      if (pos != std::string::npos)
      {
        std::string key = part.substr(0, pos);
        std::string value = part.substr(pos + 1);
        if (value.find("ull") != std::string::npos)
        {
          key1 = true;
          ds.key1 = std::stoull(value.substr(0, value.find("ull")));
        }
        else if (value.find("0x") != std::string::npos || value.find("0X") != std::string::npos)
        {
          key2 = true;
          ds.key2 = std::stoull(value, nullptr, 16);
        }
        else
        {
          ds.key3 = value;
        }
      }
      start = end + 1;
      end = line.find(':', start);
    }
  }

  if (!key1 || !key2)
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

  os << "0x" << std::uppercase << std::hex << ds.key2 << ":key3 " << std::dec;

  os << ds.key3 << (ds.key3.back() == '"' ? ":)" : ":\":)");

  return os;
}
