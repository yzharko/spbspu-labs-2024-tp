#include <bitset>
#include "dataStruct.hpp"
#include "dataTypes.hpp"
#include "delimiters.hpp"
#include "scopeguard.hpp"


std::istream& litsinger::operator>>(std::istream& is, litsinger::DataStruct& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  iofmtguard fguard(is);
  litsinger::DataStruct input;
  using del = litsinger::DelimiterIO;
  using bin = litsinger::BinULongLongIO;
  using hex = litsinger::HexULongLongIO;
  using str = litsinger::StringIO;
  is >> del{'('} >> del{':'};
  for (size_t i = 0; i < 3 && is; i++)
  {
    std::string curKey = "";
    is >> litsinger::KeyIO{curKey};

    if (curKey == "key1")
    {
      is >> bin{input.key1};
    }
    else if (curKey == "key2")
    {
      is >> hex{input.key2};
    }
    else if (curKey == "key3")
    {
      is >> str{input.key3};
    }
    is >> del{':'};
  }
  is >> del{')'};
  value = input;
  return is;
}

std::ostream& litsinger::operator<<(std::ostream& os, const litsinger::DataStruct& myStruct)
{
  iofmtguard fguard(os);
  os << "(:key1 0b" << std::bitset<8> {myStruct.key1} << ":key2 0x" << std::hex
      << std::uppercase << myStruct.key2 << ":key3 \"" << myStruct.key3 << "\":)";
  return os;
}


bool litsinger::operator<(const litsinger::DataStruct& left, const litsinger::DataStruct& right)
{
  if (left.key1 < right.key1)
  {
    return true;
  }
  else if (left.key1 == right.key1)
  {
    if (left.key2 < right.key2)
    {
      return true;
    }
    else if (left.key2 == right.key2)
    {
      if (left.key3.size() < right.key3.size())
      {
        return true;
      }
    }
  }
  return false;
}
