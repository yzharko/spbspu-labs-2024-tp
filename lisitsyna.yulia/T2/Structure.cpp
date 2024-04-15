#include "DataStruct.hpp"
#include "Structure.hpp"
#include "pattern.hpp"

#include <iostream>

std::istream& operator>>(std::istream& in, Delimiter&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Label&& dest)
{
  std::istream::sentry guard(in);
  if (!guard)
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
