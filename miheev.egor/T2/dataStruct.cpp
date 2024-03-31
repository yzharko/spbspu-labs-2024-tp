#include <utility>
#include "dataStruct.hpp"

void miheev::printDS(const DataStruct& ds)
{
  std::cout << "key1 : " << ds.key1 << '\n';
  std::cout << "key2 : " << ds.key2 << '\n';
  std::cout << "key3 : " << ds.key3 << '\n';
}

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
    std::cout << curKey << '\n';
    if (curKey == "key1")
    {
      is >> key1;
      is >> del{'l'} >> del{'l'};
      value.key1 = key1;
    }
    else if (curKey == "key2")
    {
      is >> key2;
      std::cout << "key2 = " << key2 << '\n';
      value.key2 = key2;
    }
    else if (curKey == "key3")
    {
      is >> del{'"'};
      std::getline(is, key3, '"');
      std::cout << key3 << '\n';
    }
  } while (is);
  is >> del{')'};
  return is;
}

std::ostream& operator<<(std::ostream& out, const miheev::real& value)
{
  std::cout << value.first << " / " << value.second << '\n';
  return out;
}

std::ostream& operator<<(std::ostream& out, const miheev::DataStruct& value)
{
  return out;
}