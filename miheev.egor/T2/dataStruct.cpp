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

std::istream& operator>>(std::istream& is, miheev::real& value)
{
  using del = miheev::DelimiterI;
  long long N = 0;
  unsigned long long D = 0;
  is >> del{'('} >> del{':'};
  is >> del{'N'} >> N >> del{':'};
  is >> del{'D'} >> D;
  is >> del{':'} >> del{')'};
  if (is.good())
  {
    value.first = N;
    value.second = D;
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
  is >> del{'('};
  do
  {
    std::string curKey = "";
    is >> del{':'} >> curKey;
    if (curKey == "key1")
    {
      is >> key1;
      is >> del{'l'} >> del{'l'};
      value.key1 = key1;
    }
    else if (curKey == "key2")
    {
      is >> key2;
      value.key2 = key2;
    }
    else if (curKey == "key3")
    {
      is >> del{'"'};
      std::getline(is, key3, '"');
      value.key3 = key3;
    }
  } while (is);
  is >> del{')'};
  return is;
}

std::ostream& operator<<(std::ostream& out, const miheev::real& value)
{
  std::cout << "(:N " << value.first << ":D " << value.second << ":)";
  return out;
}

std::ostream& operator<<(std::ostream& out, const miheev::DataStruct& value)
{
  out << "(:key1 " << value.key1 << "ll:key2 " << value.key2 << ":key3 \"" << value.key3 << "\":)\n";
  return out;
}