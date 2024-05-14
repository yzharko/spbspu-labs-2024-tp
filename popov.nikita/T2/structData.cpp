#include "structData.hpp"
#include "delimeter.hpp"

std::istream & popov::operator>>(std::istream & is, DoubleIO && number)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  is >> number.num;
  if (number.num == 0)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & popov::operator>>(std::istream & is, UnsLongLongIO && number)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> number.num >> DelimiterIO{'u'} >> DelimiterIO{'l'} >> DelimiterIO{'l'};
}

std::istream & popov::operator>>(std::istream & is, popov::StringIO && number)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return std::getline(is >> DelimiterIO{'"'}, number.num, '"');
}
