#include "delimiter.hpp"

std::istream & lisitsyna::operator>>(std::istream & in, Separator && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& lisitsyna::operator>>(std::istream& in, Label&& dest)
{
  std::istream::sentry guard(in);
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
