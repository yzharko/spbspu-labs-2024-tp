#include "Polygon.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include "Delimiters.hpp"

struct PolygonArea
{
  malanin:: Point first;
  double operator()(const malanin::Point& second)
  {
    double area = (second.x + first.x) * (first.y - second.y);
    first = second;
    return area;
  }
};

std::istream& malanin::operator>>(std::istream& in, Point& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = malanin::DelimiterChar;
  int x = 0;
  int y = 0;
  in >> del{ '(' } >> x >> del{ ';' } >> y >> del{ ')' };
  if (in)
  {
    value = Point{ x,y };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool malanin::operator<(const Point& p1, const Point& p2)
{
  if (p1.x != p2.x)
  {
    return p1.x < p2.x;
  }
  return p1.y < p2.y;
}

bool malanin::operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

std::istream& malanin::operator>>(std::istream& in, Polygon& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t n = 0;
  in >> n;
  if (n < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using inputItT = std::istream_iterator< malanin::Point >;
  std::vector < Point > vec;
  vec.reserve(n);
  std::copy_n(inputItT{ in }, n, std::back_inserter(vec));
  if (in && vec.size() == n)
  {
    value = Polygon{ vec };
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool malanin::operator==(const Polygon& p1, const Polygon& p2)
{
  return p1.points == p2.points;
}

double malanin::getArea(const Polygon& p)
{
  std::vector< double > partArea;
  std::transform(p.points.begin(), p.points.end(), std::back_inserter(partArea), PolygonArea{ p.points[0] });
  double area = std::accumulate(partArea.cbegin(), partArea.cend(), 0.0);
  area += (p.points[p.points.size() - 1].x + p.points[0].x) * (p.points[p.points.size() - 1].y - p.points[0].y);
  return std::abs(area) / 2;
}

bool malanin::isPerpendicular(const Point& p1, const Point& p2, const Point& p3)
{
  double x1 = p1.x - p2.x;
  double y1 = p1.y - p2.y;
  double x2 = p1.x - p3.x;
  double y2 = p1.y - p3.y;
  return x1 * x2 + y1 * y2 == 0;
}

bool malanin::isRect(const Polygon& p)
{
  if (p.points.size() != 4)
  {
    return false;
  }
  std::vector< Point > vec(p.points);
  std::sort(vec.begin(), vec.end());
  return isPerpendicular(vec[0], vec[1], vec[2]) && isPerpendicular(vec[1], vec[0], vec[3]) && isPerpendicular(vec[3], vec[2], vec[1]);
}

bool malanin::isOddCountVertexes(const Polygon& p)
{
  return p.points.size() % 2;
}

bool malanin::isEvenCountVertexes(const Polygon& p)
{
  return p.points.size() % 2 == 0;
}

bool malanin::isNCountVertexes(const Polygon& p, size_t n)
{
  return p.points.size() == n;
}

bool malanin::minArea(const Polygon& p1, const Polygon& p2)
{
  return getArea(p1) < getArea(p2);
}

bool malanin::minVertexes(const Polygon& p1, const Polygon& p2)
{
  return p1.points.size() < p2.points.size();
}
