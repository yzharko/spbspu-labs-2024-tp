#include "GeometryUtils.hpp"
#include <cmath>

double GeometryUtils::calculateArea(const Polygon& polygon) const
{
  int n = polygon.points.size();
  double area = 0.0;
  for (int i = 0; i < n; ++i)
  {
    int j = (i + 1) % n;
    area += polygon.points[i].x * polygon.points[j].y;
    area -= polygon.points[j].x * polygon.points[i].y;
  }
  return std::abs(area) / 2.0;
}
