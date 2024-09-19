#include "commands.hpp"
#include <cctype>
#include <functional>
#include <numeric>
#include <algorithm>
#include <utility>

double sobolevsky::areaIf(double result, const Polygon & polygon, size_t mode, bool inpMode)
{
  bool mode1 = (inpMode && polygon.points.size() == mode);
  bool mode2 = (mode == 2 && !inpMode);
  bool mode3 = (mode == (polygon.points.size() % 2) && !inpMode);
  if (mode1 || mode2 || mode3)
  {
    result += getArea(polygon);
  }
  return result;
}

bool sobolevsky::getMaxMinArea(const Polygon & polygon1, const Polygon & polygon2)
{
  return getArea(polygon1) < getArea(polygon2);
}

bool sobolevsky::getMaxMinVertex(const Polygon & polygon1, const Polygon & polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

bool sobolevsky::countIf(const Polygon & polygon, size_t mode, bool inpMode)
{
  bool mode1 = (inpMode && polygon.points.size() == mode);
  bool mode2 = (!inpMode && mode == (polygon.points.size()) % 2);
  bool mode3 = (!inpMode && mode == (polygon.points.size()) % 2);
  if (mode1 || mode2 || mode3)
  {
    return true;
  }
  return false;
}

long long sobolevsky::areaTriangl(Point a, Point b, Point c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool sobolevsky::intersect_1(int a, int b, int c, int d)
{
  if (a > b)
  {
    std::swap(a, b);
  }

  if (c > d)
  {
    std::swap(c, d);
  }

  return std::max(a, c) <= std::min(b, d);
}

bool sobolevsky::intersectVectorPointOnLine(Point a, Point b, Point c)
{
  return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y) == 0;
}

bool sobolevsky::intersectVectors(Point a, Point b, const Polygon & polygon, size_t i)
{
  Point c = polygon.points[i];
  Point d = polygon.points[(i + 1) % polygon.points.size()];
  bool intersect_1Checks = intersect_1(a.x, b.x, c.x, d.x) && intersect_1(a.y, b.y, c.y, d.y);
  bool areaTrianglChecks = areaTriangl(a,b,c) * areaTriangl(a,b,d) <= 0 && areaTriangl(c,d,a) * areaTriangl(c,d,b) <= 0;
  bool pointOnLineChecks = intersectVectorPointOnLine(a, b, c) || intersectVectorPointOnLine(a, b, d)
  || intersectVectorPointOnLine(c, d, a) || intersectVectorPointOnLine(c, d, b);
  return (intersect_1Checks && areaTrianglChecks) || pointOnLineChecks;
}

bool sobolevsky::intersectPolygAndVect(const Polygon & polygon1, const Polygon & polygon2, size_t i)
{
  Point a = polygon1.points[i];
  Point b = polygon1.points[(i + 1) % polygon1.points.size()];
  std::vector< size_t > v(polygon2.points.size());
  std::iota(v.begin(), v.end(), 0);
  using namespace std::placeholders;
  std::function< bool(size_t) > bindIntersectPolygAndVect = std::bind(intersectVectors, a, b, polygon2, _1);
  if (std::count_if(v.cbegin(), v.cend(), bindIntersectPolygAndVect) > 0)
  {
    return true;
  }
  return false;
}

bool sobolevsky::intersectPolyg(const Polygon & polygon1, const Polygon & polygon2)
{
  std::vector< size_t > v(polygon1.points.size());
  std::iota(v.begin(), v.end(), 0);
  using namespace std::placeholders;
  std::function< bool(size_t) > bindIntersectPolyg = std::bind(intersectPolygAndVect, polygon1, polygon2, _1);
  if (std::count_if(v.cbegin(), v.cend(), bindIntersectPolyg) > 0)
  {
    return true;
  }
  return false;
}

bool sobolevsky::findDifference(const Polygon & polyg1, const Polygon & polyg2, int difX, int difY, int i)
{
  if (((polyg1.points[i].x - polyg2.points[i].x) != difX) || ((polyg1.points[i].y - polyg2.points[i].y) != difY))
  {
    return true;
  }
  return false;
}

bool sobolevsky::isSamePolyg(const Polygon & polyg1, const Polygon & polyg2)
{
  if (polyg1.points.size() == polyg2.points.size())
  {
    int difX, difY;
    difX = polyg1.points[0].x - polyg2.points[0].x;
    difY = polyg1.points[0].y - polyg2.points[0].y;
    std::vector< int > v(polyg1.points.size() - 1);
    std::iota(v.begin(), v.end(), 1);
    using namespace std::placeholders;
    std::function< bool(int) > bindFindDifference = std::bind(findDifference, polyg1, polyg2, difX, difY, _1);
    if (std::count_if(v.cbegin(), v.cend(), bindFindDifference) == 0)
    {
      return true;
    }
  }
  return false;
}

void sobolevsky::error(std::ostream & out, const std::string & text)
{
  out << text;
}

void sobolevsky::areaOutput(const std::vector< Polygon > & vec, std::ostream & out, int mode1, bool mode2)
{
  using namespace std::placeholders;
  std::function< double(double, const Polygon &) > bindareaIf = std::bind(areaIf, _1, _2, mode1, mode2);
  if (!mode2 && mode1 == 2)
  {
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) / vec.size() << "\n";
  }
  else
  {
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
}

void sobolevsky::area(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    areaOutput(vec, out, 0, false);
  }
  else if (arg == "ODD")
  {
    areaOutput(vec, out, 1, false);
  }
  else if (arg == "MEAN")
  {
    if (vec.size() == 0)
    {
      throw std::exception();
    }
    areaOutput(vec, out, 2, false);
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    areaOutput(vec, out, stoll(arg), true);
  }
}

void sobolevsky::getMax(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (vec.size() == 0)
  {
    throw std::exception();
  }
  if (arg == "AREA")
  {
    out << getArea(*std::max_element(vec.cbegin(), vec.cend(), getMaxMinArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << std::max_element(vec.cbegin(), vec.cend(), getMaxMinVertex)->points.size() << "\n";
  }
}

void sobolevsky::getMin(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (vec.size() == 0)
  {
    throw std::exception();
  }
  if (arg == "AREA")
  {
    out << getArea(*std::min_element(vec.cbegin(), vec.cend(), getMaxMinArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << std::min_element(vec.cbegin(), vec.cend(), getMaxMinVertex)->points.size() << "\n";
  }
}

void sobolevsky::countOutput(const std::vector< Polygon > & vec, std::ostream & out, int mode1, bool mode2)
{
  using namespace std::placeholders;
  std::function< bool(const Polygon &) > bindVertEven = std::bind(countIf, _1, mode1, mode2);
  out << std::count_if(vec.cbegin(), vec.cend(), bindVertEven) << "\n";
}

void sobolevsky::count(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    countOutput(vec, out, 0, false);
  }
  else if (arg == "ODD")
  {
    countOutput(vec, out, 1, false);
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    countOutput(vec, out, stoll(arg), true);
  }
}

bool sobolevsky::isEqual(const Polygon & polyg1, const Polygon & polyg2)
{
  return polyg1.points.size() == polyg2.points.size();
}

void sobolevsky::intersections(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  Polygon inpPolyg;
  in >> inpPolyg;
  if (!in)
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  std::function< bool(const Polygon &) > findEqual = std::bind(isEqual, inpPolyg, _1);
  if (std::count_if(vec.cbegin(), vec.cend(), findEqual) == 0)
  {
    throw std::exception();
  }
  std::function< bool(const Polygon &) > bindIntersection = std::bind(intersectPolyg, inpPolyg, _1);
  out << std::count_if(vec.cbegin(), vec.cend(), bindIntersection) << "\n";
}

void sobolevsky::same(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  Polygon inpPolyg;
  in >> inpPolyg;
  if (!in)
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  std::function< bool(const Polygon &) > findEqual = std::bind(isEqual, inpPolyg, _1);
  if (std::count_if(vec.cbegin(), vec.cend(), findEqual) == 0)
  {
    throw std::exception();
  }
  std::function< bool(const Polygon &) > bindSame = std::bind(isSamePolyg, inpPolyg, _1);
  out << std::count_if(vec.cbegin(), vec.cend(), bindSame) << "\n";
}
