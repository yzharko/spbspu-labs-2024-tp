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
    std::vector< Polygon > figure;
    Polygon result;
    Point input;
    {
      using sep = DelimiterIO;
      size_t countPoints = 0;

      if (!(in >> countPoints))
      {
        in.setstate(std::ios::failbit);
      }

      for (size_t i = 0; i < countPoints; i++)
      {
        in >> sep{ '(' } >> input.x;
        in >> sep{ ';' } >> input.y;
        in >> sep{ ')' };
        if (in)
        {
          result.points.emplace_back(input);
        }
      }

      if (countPoints != result.points.size() || result.points.size() <= 2)
      {
        in.setstate(std::ios::failbit);
      }
    }
    if (in)
    {
      dest = result;
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
