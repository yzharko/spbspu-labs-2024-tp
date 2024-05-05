#include "commands.hpp"
#include <cctype>
#include <functional>
#include <numeric>
#include <algorithm>
#include <utility>

double sobolevsky::areaIf(double result, const Polygon & polygon, size_t mode, bool inpMode)
{
  if (inpMode && polygon.points.size() == mode)
  {
    result += getArea(polygon);
  }
  if (mode == 2 && !inpMode)
  {
    result += getArea(polygon);
  }
  else if (mode == (polygon.points.size() % 2) && !inpMode)
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

size_t sobolevsky::countIf(size_t result, const Polygon & polygon, size_t mode, bool inpMode)
{
  if (inpMode && polygon.points.size() == mode)
  {
    result += 1;
  }
  else if (!inpMode && mode == (polygon.points.size()) % 2)
  {
    result += 1;
  }
  else if (!inpMode && mode == (polygon.points.size()) % 2)
  {
    result += 1;
  }
  return result;
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
  return (intersect_1(a.x, b.x, c.x, d.x) && intersect_1(a.y, b.y, c.y, d.y)
  && areaTriangl(a,b,c) * areaTriangl(a,b,d) <= 0 && areaTriangl(c,d,a) * areaTriangl(c,d,b) <= 0)
  || intersectVectorPointOnLine(a, b, c) || intersectVectorPointOnLine(a, b, d)
  || intersectVectorPointOnLine(c, d, a) || intersectVectorPointOnLine(c, d, b);
}

bool sobolevsky::intersectPolygAndVect(const Polygon & polygon1, const Polygon & polygon2, size_t i)
{
  Point a = polygon2.points[i];
  Point b = polygon2.points[(i + 1) % polygon1.points.size()];
  std::vector< size_t > v(polygon1.points.size());
  std::iota(v.begin(), v.end(), 0);
  using namespace std::placeholders;
  std::function< bool(size_t) > bindIntersectPolygAndVect = std::bind(intersectVectors, a, b, polygon1, _1);
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
  std::function< bool(size_t) > bindIntersectPolygAndVect = std::bind(intersectPolygAndVect, polygon2, polygon1, _1);
  if (std::count_if(v.cbegin(), v.cend(), bindIntersectPolygAndVect) > 0)
  {
    return true;
  }
  return false;
}

bool sobolevsky::isSamePolyg(const Polygon & polyg1, const Polygon & polyg2)
{
  bool isSame = false;
  if (polyg1.points.size() == polyg2.points.size())
  {
    isSame = true;
    int difX, difY;
    difX = polyg1.points[0].x - polyg2.points[0].x;
    difY = polyg1.points[0].y - polyg2.points[0].y;
    for (size_t i = 1; i < polyg1.points.size(); i++)
    {
      if (((polyg1.points[i].x - polyg2.points[i].x) != difX) || ((polyg1.points[i].y - polyg2.points[i].y) != difY))
      {
        isSame = false;
        break;
      }
    }
  }
  return isSame;
}

void sobolevsky::area(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    using namespace std::placeholders;
    std::function< double(double, const Polygon &) > bindareaIf = std::bind(areaIf, _1, _2, 0, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
  else if (arg == "ODD")
  {
    using namespace std::placeholders;
    std::function< double(double, const Polygon &) > bindareaIf = std::bind(areaIf, _1, _2, 1, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
  else if (arg == "MEAN")
  {
    if (vec.size() == 0)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< double(double, const Polygon &) > bindareaIf = std::bind(areaIf, _1, _2, 2, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) / vec.size() << "\n";
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< double(double, const Polygon &) > bindareaIf = std::bind(areaIf, _1, _2, stoll(arg), true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
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

void sobolevsky::count(const std::vector< Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    using namespace std::placeholders;
    std::function< size_t(size_t, const Polygon &) > bindVertEven = std::bind(countIf, _1, _2, 0, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertEven) << "\n";
  }
  else if (arg == "ODD")
  {
    using namespace std::placeholders;
    std::function< size_t(size_t, const Polygon &) > bindVertOdd = std::bind(countIf, _1, _2, 1, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertOdd) << "\n";
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< size_t(size_t, const Polygon &) > bindVertNum = std::bind(countIf, _1, _2, stoll(arg), true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertNum) << "\n";
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
