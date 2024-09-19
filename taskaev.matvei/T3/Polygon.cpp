#include <iterator>
#include <algorithm>
#include <delimeter.hpp>
#include "Polygon.hpp"

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

  bool operator==(const Polygon& first, const Polygon& second)
  {
    return first.points == second.points;
  }

  bool operator==(const Point& first, const Point& second)
  {
    return first.x_ == second.x_ && first.y_ == second.y_;
  }
}
