#include <sstream>
#include <iomanip>
#include "DataStruct.h"

std::istream& operator>>(std::istream& is, DataStruct& data)
{
  std::string input, part;
  if (std::getline(is, input, ')'))
  {
    std::istringstream iss(input.substr(input.find('(') + 1));
    while (std::getline(iss, part, ':'))
    {
      std::string key, value;
      std::getline(iss, key, ' ');
      std::getline(iss, value, ':');
      if (key == "key1" || key == "key2")
      {
        unsigned long long* key_ptr = (key == "key1") ? &data.key1 : &data.key2;
        if (value.find("ull") != std::string::npos || value.find("ULL") != std::string::npos)
        {
          *key_ptr = std::stoull(value.substr(0, value.find("ull")));
        }
        else if (value.find("0x") != std::string::npos || value.find("0X") != std::string::npos)
        {
          *key_ptr = std::stoull(value, nullptr, 16);
        }
      }
      else if (key == "key3")
      {
        data.key3 = value.substr(1, value.length() - 2);
      }
    }
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data)
{
  os << "(:key1 " << data.key1 << "ull:key2 " << data.key2 << "ull:key3 \"" << data.key3 << "\":)";
  return os;
}
