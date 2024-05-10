#include "geometry.hpp"

std::istream & zheleznyakov::operator>>(std::istream & in, Point & ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  };
  return in >> SeparatorIO{'('} >> IntIO{ref.x} >> SeparatorIO{';'} >> IntIO{ref.y} >> SeparatorIO{')'};
};

std::ostream & zheleznyakov::operator<<(std::ostream & out, const Point & ref)
{
  return out << '(' << ref.x << ';' << ref.y << ')';
};

std::istream & zheleznyakov::operator>>(std::istream & in, Polygon & ref)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  };
  size_t pointsCount;
  in >> SizeTIO{pointsCount};
  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
  }
  for (size_t i = 0; i < pointsCount; i++)
  {
    Point currentPoint{};
    in >> currentPoint;
    ref.points.push_back(currentPoint);
  }
  return in;
};

std::ostream & zheleznyakov::operator<<(std::ostream & out, const Polygon & ref)
{
  for (size_t i = 0; i < ref.points.size(); i++)
  {
    out << ref.points.at(i);
    out << (i == ref.points.size() - 1 ?'\n' : ' ');
  }
  return out;
}
