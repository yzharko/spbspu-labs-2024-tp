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

double zheleznyakov::calculateCrossProduct(const Point & p1, const Point & p2)
{
  return p1.x * p2.y - p1.y * p2.x;
}

double zheleznyakov::calculatePolygonArea(const Polygon & poly, int i, double area)
{
  int n = poly.points.size();
  if (i < n - 1) {
    area += calculateCrossProduct(poly.points[i], poly.points[i + 1]);
    return calculatePolygonArea(poly, i + 1, area);
  } else {
    area += calculateCrossProduct(poly.points[n - 1], poly.points[0]);
    area = std::abs(area) / 2.0;
    return area;
  }
}
