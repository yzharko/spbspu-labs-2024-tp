#include "polygon.hpp"
#include "taskTypes.hpp"
#include "delim.hpp"
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
  {
    using intgr = intIO;
    size_t numOfPoints = 0;
    in >> numOfPoints;
    std::string keyNum;
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
  }
  if (in)
  {
    data = curPoly;
  }
  return in;
}

//std::ostream& psarev::operator<<(std::ostream& out, const Polygon& data)
//{
//}

//bool psarev::operator<(const Polygon& first, const Polygon& second)
//{
//}