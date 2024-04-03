#include <utility>
#include "dataStruct.hpp"
#include "dataTypes.hpp"
#include "delimiters.hpp"
#include "scopeguard.hpp"


std::istream& miheev::operator>>(std::istream& is, miheev::DataStruct& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  iofmtguard fguard(is);
  miheev::DataStruct input;
  using del = miheev::DelimiterIO;
  using rl = miheev::RealIO;
  using ll = miheev::LongLongIO;
  using str = miheev::StringIO;
  is >> del{'('} >> del{':'};
  for (size_t i = 0; i < 3 && is; i++)
  {
    std::string curKey = "";
    is >> miheev::KeyIO{curKey};
    if (curKey == "key1")
    {
      is >> ll{input.key1};
    }
    else if (curKey == "key2")
    {
      is >> rl{input.key2};

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

std::ostream& miheev::operator<<(std::ostream& out, const miheev::DataStruct& value)
{
  iofmtguard fguard(out);
  out << "(:key1 " << value.key1 << "ll:key2 " << value.key2 << ":key3 \"" << value.key3 << "\":)";
  return out;
}


bool miheev::operator<(const miheev::DataStruct& lhs, const miheev::DataStruct& rhs)
{
  if (lhs.key1 < rhs.key1 or lhs.key2 < rhs.key2 or lhs.key3.size() < lhs.key3.size())
  {
    return true;
  }
  return false;
}

