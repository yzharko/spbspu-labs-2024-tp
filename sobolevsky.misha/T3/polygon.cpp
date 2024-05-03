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

double sobolevsky::Polygon::getArea()
{
  double area = 0;
  std::cout << points.size() << "\n";
  for (int i = 0; i < points.size(); i++)
  {
    if (i == points.size())
    {
      area += (points[i].x * points[0].y - points[i].y * points[0].x);
    }
    else
    {
      area += (points[i].x * points[i+1].y - points[i].y * points[i+1].x);
    }
  }
  return 0.5 * abs(area);
}
