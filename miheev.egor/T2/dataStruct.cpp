#include <utility>
#include "dataStruct.hpp"

std::istream& operator>>(std::istream& is, miheev::DelimiterI&& exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& operator>>(std::istream& is, miheev::DataStruct& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  using del = miheev::DelimiterI;
  long long key1;
  miheev::real key2;
  std::string key3;
  std::string curKey;
  is >> del{'('} >> del{':'} >> curKey;
  if (curKey == "key1")
}

std::ostream& operator<<(std::ostream& out, const miheev::DataStruct& value)
{

}