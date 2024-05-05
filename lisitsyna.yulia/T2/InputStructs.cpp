#include "InputStructs.hpp"
#include <iomanip>

std::istream& lisitsyna::operator>>(std::istream& in, Label&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    std::string data = "";
    if ((in >> StringKey{ data }) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& lisitsyna::operator>>(std::istream& in, LongLong&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> dest.ref >> Delimiter{ 'l' } >> Delimiter{ 'l' };
}

std::istream& lisitsyna::operator>>(std::istream& in, Char&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> Delimiter('\'') >> dest.ref >> Delimiter('\'');
}

std::istream& lisitsyna::operator>>(std::istream& in, StringKey&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> Delimiter{ '"' }, dest.ref, '"');
}
