#include <iostream>
#include "polygon.hpp"
#include "scopeGuard.hpp"

using delim = psarev::DelimiterIO;
std::istream& psarev::operator>>(std::istream& in, Polygon& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Polygon curPoly;
  Point inPoint;
  using intgr = intIO;
  size_t numOfPoints = 0;
  if (!(in >> numOfPoints) || numOfPoints <= 2)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  for (size_t i = 0; i < numOfPoints; ++i)
  {
    in >> delim{ '(' } >> intgr{ inPoint.x };
    in >> delim{ ';' } >> intgr{ inPoint.y };
    in >> delim{ ')' };

    if (in)
    {
      curPoly.points.emplace_back(inPoint);
    }
  }
  if (in && (numOfPoints == curPoly.points.size()))
  {
    data = curPoly;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& psarev::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
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

using delim = psarev::DelimiterIO;

std::istream& psarev::operator>>(std::istream& in, intIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
}
