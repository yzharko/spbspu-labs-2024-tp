#include "dataTypes.hpp"
#include <iostream>

std::istream& miheev::operator>>(std::istream& in, miheev::IntIO&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> value.ref;
}

std::istream& miheev::operator>>(std::istream& in, miheev::SizeTIO&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> value.ref;
}
