#include "polygon.hpp"

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <numeric>

#include "ScopeGuard.hpp"
#include "Delimeter.hpp"

namespace lisitsyna
{
  bool comparatorVertexes(Polygon fst, Polygon snd)
  {
    return (fst.points.size() > snd.points.size());
  }

  bool comparatorArea(Polygon fst, Polygon snd)
  {
    return (getArea(fst) > getArea(snd));
  }

  bool operator==(Point& src1, Point& src2)
  {
    return ((src1.x == src2.x) && (src1.y == src2.y));
  }

  bool operator==(Polygon& src1, Polygon& src2)
  {
    if (src1.points.size() == src2.points.size())
    {
      return std::equal(src1.points.begin(), src1.points.end(), src2.points.begin());
    }
    return false;;
  }

  bool operator!=(Polygon& src1, Polygon& src2)
  {
    return !(src1 == src2);
  }

  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimeterIO('(');
    in >> dest.x;
    in >> DelimeterIO(';');
    in >> dest.y;
    in >> DelimeterIO(')');
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    std::size_t amount = 0;
    in >> amount;
    Polygon inPolygon;
    std::copy_if(
      std::istream_iterator< Point >(in),
      std::istream_iterator< Point >(),
      std::back_inserter(inPolygon.points),
      [&in](const Point&)
      {
        if (in.peek() == '\n')
        {
          in.setstate(std::ios_base::eofbit);
        }
        return true;
      }
    );
    in.clear();
    in.ignore(256, '\n');
    if (amount != inPolygon.points.size() || inPolygon.points.size() < 3)
    {
      in.setstate(std::ios_base::failbit);
    }
    if (in)
    {
      dest = inPolygon;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Point& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    iofmtguard fmtguard(out);
    out << "(" << dest.x << ";";
    out << dest.y << ")";
    return out;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& dest)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    iofmtguard fmtguard(out);
    out << dest.points.size();
    out << " ";
    for (size_t i = 0; i < dest.points.size(); i++)
    {
      out << dest.points[i];
      out << " ";
    }
    return out;
  }

  double getArea(const Polygon& data)
  {
    Polygon tmp = data;
    tmp.points.push_back(data.points[0]);
    double area;
    auto getPoint = [&](Point a, Point b)
    {
      return a.x * b.y - a.y * b.x;
    };
    std::vector< double > arr;
    std::transform(tmp.points.begin(), tmp.points.end() - 1, tmp.points.begin() + 1,
    std::back_inserter(arr), getPoint);
    area = std::accumulate(arr.begin(), arr.end(), 0.0);
    return std::abs(area * 0.5);
  }

  bool isParallelogram(const Polygon& data)
  {
    if (data.points.size() == 4)
    {
      Point p1 = data.points[0];
      Point p2 = data.points[1];
      Point p3 = data.points[2];
      Point p4 = data.points[3];
      return (((p2.x - p1.x) == (p3.x - p4.x)) && ((p4.y - p1.y) == (p3.y - p2.y)));
      return (((p2.y - p1.y) == (p3.y - p4.y)) && ((p4.x - p1.x) == (p3.x - p2.x)));
    }
    return false;
  }

  bool isRect(const Polygon& data)
  {
    if (data.points.size() == 4)
    {
      Point p1 = data.points[0];
      Point p2 = data.points[1];
      Point p3 = data.points[2];
      Point p4 = data.points[3];
      if (isParallelogram(data))
      {
        return ((p2.x - p1.x) * (p2.x - p1.x) + (p4.y - p1.y) * (p4.y - p1.y)) ==
        ((p3.y - p2.y) * (p3.y - p2.y) + (p3.x - p4.x) * (p3.x - p4.x));
      }
    }
    return false;
  }
}
