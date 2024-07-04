#include "dataStruct.hpp"
#include "delimiter.hpp"

namespace nikiforov
{
  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon resPolygon;
    Point inputCoord;
    {
      using sep = DelimiterIO;
      size_t countPoints = 0;

      if (!(in >> countPoints) || countPoints <= 2)
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      for (size_t i = 0; i < countPoints; i++)
      {
        if (in.get() == '\n')
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        in >> sep{ '(' } >> inputCoord.x;
        in >> sep{ ';' } >> inputCoord.y;
        in >> sep{ ')' };
        if (in)
        {
          resPolygon.points.emplace_back(inputCoord);
        }
      }

      if (countPoints != resPolygon.points.size() || in.get() != '\n')
      {
        in.setstate(std::ios::failbit);
      }
    }
    if (in)
    {
      dest = resPolygon;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    for (size_t i = 0; i < src.points.size(); i++)
    {
      out << "(" << src.points[i].x << "," << src.points[i].y << ")";
    }
    return out;
  }
}
