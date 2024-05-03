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

double sobolevsky::getArea(const sobolevsky::Polygon& polygon)
{
  double area = 0;
  for (int i = 0; i < polygon.points.size(); i++)
  {
    if (i == polygon.points.size() - 1)
    {
      area += (polygon.points[i].x * polygon.points[0].y - polygon.points[i].y * polygon.points[0].x);
    }
    else
    {
      area += (polygon.points[i].x * polygon.points[i+1].y - polygon.points[i].y * polygon.points[i+1].x);
    }
  }
  return 0.5 * abs(area);
}
