#include <iostream>
#include "dataTypes.hpp"
#include "delimiters.hpp"

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

std::ostream& miheev::operator<<(std::ostream& out, const miheev::real& value)
{
  std::cout << "(:N " << value.first << ":D " << value.second << ":)";
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
