#include <utility>
#include "dataStruct.hpp"

std::istream& miheev::operator>>(std::istream& is, miheev::DelimiterIO&& exp)
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

std::istream& miheev::operator>>(std::istream& is, miheev::LongLongIO&& value)
{
  using del = miheev::DelimiterIO;
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> value.ref >> del{'l'} >> del{'l'};
  return is;
}

std::istream& miheev::operator>>(std::istream& is, miheev::RealIO&& value)
{
  using del = miheev::DelimiterIO;
  using lab = miheev::LabelIO;
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> del{'('} >> del{':'} >> lab{"N"};
  is >> value.ref.first;
  is >> del{':'} >> lab{"D"};
  is >> value.ref.second;
  is >> del{':'} >> del{')'};
  return is;
}

std::istream& miheev::operator>>(std::istream& is, miheev::StringIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(is >> miheev::DelimiterIO{'"'}, value.ref, '"');
}

std::istream& miheev::operator>>(std::istream& is, miheev::LabelIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  std::string data = "";
  is >> data;
  bool cmp = data != value.exp;
  if (is and cmp)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& miheev::operator>>(std::istream& is, miheev::KeyIO&& value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> value.ref;
  if (value.ref != "key1" and value.ref != "key2" and value.ref != "key3")
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream& miheev::operator>>(std::istream& is, miheev::DataStruct& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
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

std::ostream& miheev::operator<<(std::ostream& out, const miheev::real& value)
{
  std::cout << "(:N " << value.first << ":D " << value.second << ":)";
  return out;
}

std::ostream& miheev::operator<<(std::ostream& out, const miheev::DataStruct& value)
{
  out << "(:key1 " << value.key1 << "ll:key2 " << value.key2 << ":key3 \"" << value.key3 << "\":)";
  return out;
}

bool miheev::operator<(const miheev::real& lhs, const miheev::real& rhs)
{
  long long difference = lhs.first*rhs.second - rhs.first*lhs.second;
  if (difference < 0)
  {
    return true;
  }
  return false;
}

bool miheev::operator<(const miheev::DataStruct& lhs, const miheev::DataStruct& rhs)
{
  if (lhs.key1 < rhs.key1 or lhs.key2 < rhs.key2 or lhs.key3.size() < lhs.key3.size())
  {
    return true;
  }
  return false;
}

miheev::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

miheev::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
