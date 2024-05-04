#include "polygon.hpp"
#include <iostream>

std::istream & khoroshkin::operator>>(std::istream & is, DelimiterIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = '0';
  is >> c;
  if (is && (c != dest.exp))
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}
std::istream & khoroshkin::operator>>(std::istream & is, Point & dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  using sep = DelimiterIO;
  Point point;
  is >> sep{ '(' } >> point.x >> sep{ ';' } >> point.y >> sep{ ')' };
  if (is)
  {
    dest = point;;
  }
  return is;
}

std::istream & khoroshkin::operator>>(std::istream & is, Polygon & dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  Polygon polygon;
  size_t vertexes;
  if (!(is >> vertexes))
  {
    is.setstate(std::ios::failbit);
  }
  Point point;
  for (size_t i = 0; i < vertexes; i++)
  {
    is >> point;
    if (is)
    {
      polygon.points.push_back(point);
    }
  }
  if (vertexes != polygon.points.size() || polygon.points.size() <= 2)
  {
    is.setstate(std::ios::failbit);
  }
  if (is)
  {
    dest = polygon;
  }
  return is;
}
