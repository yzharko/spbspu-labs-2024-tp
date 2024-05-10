#include <iterator>
#include <algorithm>
#include "Polygon.hpp"
#include "delimeter.hpp"


namespace taskaev
{
  std::istream& operator>>(std::istream& in, Point& point)
  {
    using del = DelimeterI;
    std::istream::sentry guard(in);
    if(!guard)
    {
      return in;
    }
    return in >> del{'('} >> point.x_ >> del{';'} >> point.y_ >> del{')'};
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon input;
    size_t points = 0;
    in >> points;
    if (points < 3)
    {
      in.setstate(std::ios::failbit);
    }
    input.points.reserve(points);
    std::copy_n(
      std::istream_iterator< Point >(in),
      points,
      std::back_inserter(input.points)
    );

    if (in)
    {
      polygon.points.swap(input.points);
    }
    return in;
  }
}
