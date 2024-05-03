#include "polygon.hpp"
#include <iterator>
#include <algorithm>

std::istream& sobolevsky::operator>>(std::istream& in, sobolevsky::Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexCount = 0;
  in >> vertexCount;
  if (vertexCount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  for(size_t i = 0; i < vertexCount; i++)
  {
    sobolevsky::Point temp;
    in >> temp;
    polygon.points.push_back(temp);
  }
  return in;
}
