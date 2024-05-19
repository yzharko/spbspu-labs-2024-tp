#include "geometry.hpp"
#include <limits>
#include <iostream>
#include <string>

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
  }
  size_t pointsAmount = 0;
  in >> SizeTIO{pointsAmount};
  if (pointsAmount < 3)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector< Point > polygon;
  for (size_t i = 0; i < pointsAmount; i++)
  {
    Point temp{};
    in >> temp;
    polygon.push_back(temp);
  }
  if (polygon.size() != pointsAmount || in.get() != '\n')
  {
    in.setstate(std::ios::failbit);
  }
  ref = Polygon{polygon};
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

bool zheleznyakov::operator==(const Point & point1, const Point & point2)
{
  return point1.x == point2.x && point1.y == point2.y;
}

bool zheleznyakov::operator==(const Polygon & poly1, const Polygon & poly2)
{
  return std::equal(
    std::begin(poly1.points), std::end(poly1.points),
    std::begin(poly2.points), std::end(poly2.points)
  );
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
