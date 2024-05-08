#include <iostream>
#include <utility>
#include "point.hpp"

std::istream& kovshikov::operator>>(std::istream & is, Int&& integer)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return is >> integer.value;
}

std::istream& kovshikov::operator>>(std::istream& is, Point& value)
{
  std::istream::sentry guard(is); // библиотека?
  if(!guard)
  {
    return is;
  }
  iofmtguard fmtguard(is); //защита потока
  Point point;
  is >> Del{'('};
  is >> Int{point.x} >> Del{';'};
  is >> Int{point.y} >> Del{')'};
  if(is)
  {
    value = point;
  }
  return is;
}

std::ostream& kovshikov::operator<<(std::ostream& out, const Point& value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  out << value.x << " " << value.y;
  return out;
}

