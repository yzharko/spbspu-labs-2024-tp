#include "DataStruct.hpp"

std::istream& kaseev::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = 0;
  in >> c;
  if (c != data.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
