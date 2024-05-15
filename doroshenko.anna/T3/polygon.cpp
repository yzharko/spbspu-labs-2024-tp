#include "polygon.hpp"
#include <iostream>
#include <algorithm>
#include "structures.hpp"

std::istream& doroshenko::operator>>(std::istream& input, Point& dest)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using separator = DelimiterIO;
  if (!(input >> separator{ '(' } >> dest.x >> separator{ ';' } >> dest.y >> separator{ ')' }))
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& doroshenko::operator>>(std::istream& input, Polygon& dest)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  Polygon polygon;
  size_t vertexes;
  if (!(input >> vertexes) || vertexes < 3)
  {
    input.setstate(std::ios::failbit);
  }
  using input_it_t = std::istream_iterator< Point >;
  std::vector< Point > points;
  std::copy_n(input_it_t{ input }, vertexes, std::back_inserter(points));
  if (input)
  {
    polygon.points = std::move(points);
  }
  if (input && vertexes == polygon.points.size())
  {
    dest = polygon;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

bool doroshenko::Point::operator==(const Point& other) const
{
  return x == other.x && y == other.y;
}

bool doroshenko::Polygon::operator==(const Polygon& other) const
{
  if(points.size() != other.points.size())
  {
    return false;
  }
  return std::equal(other.points.begin(), other.points.end(),
                        points.begin(), points.end());
}
