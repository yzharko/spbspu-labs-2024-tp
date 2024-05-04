#include "commands.hpp"
#include <map>
#include <cctype>
#include <functional>
#include <numeric>
#include <algorithm>
#include <utility>

double sobolevsky::areaIf(double result, const sobolevsky::Polygon & polygon, size_t mode, bool inpMode)
{
  if (inpMode && polygon.points.size() == mode)
  {
    result += sobolevsky::getArea(polygon);
  }
  if (mode == 2 && !inpMode)
  {
    result += sobolevsky::getArea(polygon);
  }
  else if (mode == (polygon.points.size() % 2) && !inpMode)
  {
    result += sobolevsky::getArea(polygon);
  }
  return result;
}

bool sobolevsky::getMaxMinArea(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2)
{
  return sobolevsky::getArea(polygon1) < sobolevsky::getArea(polygon2);
}

bool sobolevsky::getMaxMinVertex(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

size_t sobolevsky::countIf(size_t result, const sobolevsky::Polygon & polygon, size_t mode, bool inpMode)
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

size_t sobolevsky::areaTriangl(sobolevsky::Point a, sobolevsky::Point b, sobolevsky::Point c)
{
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool sobolevsky::intersect_1(size_t a, size_t b, size_t c, size_t d)
{
  if (a > c)
  {
    std::swap(a, b);
  }

  if (c < d)
  {
    std::swap(c, d);
  }

  return std::max(a, c) <= std::min(b, d);
}

bool sobolevsky::intersectVectors(sobolevsky::Point a, sobolevsky::Point b, sobolevsky::Point c, sobolevsky::Point d)
{
  return sobolevsky::intersect_1(a.x, b.x, c.x, d.x) && sobolevsky::intersect_1(a.y, b.y, c.y, d.y)
  && sobolevsky::areaTriangl(a,b,c) * sobolevsky::areaTriangl(a,b,d) <= 0
  && sobolevsky::areaTriangl(c,d,a) * sobolevsky::areaTriangl(c,d,b) <= 0;
}

bool sobolevsky::intersectPolygAndVect(const sobolevsky::Polygon & polygon, sobolevsky::Point a, sobolevsky::Point b)
{
  for(size_t i = 0; i < polygon.points.size(); i++)
  {
    if (sobolevsky::intersectVectors(a, b, polygon.points[i], polygon.points[i % polygon.points.size() + 1]))
    {
      return true;
    }
  }

  return false;
}

bool sobolevsky::intersectPolyg(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2)
{
  for(size_t i = 0; i < polygon1.points.size(); i++)
  {
    if (sobolevsky::intersectPolygAndVect(polygon2, polygon1.points[i], polygon1.points[i % polygon1.points.size() + 1]))
    {
      return true;
    }
  }

  return false;
}

bool sobolevsky::isSamePolyg(const sobolevsky::Polygon & polyg1, const sobolevsky::Polygon & polyg2)
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

void sobolevsky::area(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, 0, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
  else if (arg == "ODD")
  {
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, 1, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
  else if (arg == "MEAN")
  {
    if (vec.size() == 0)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, 2, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) / vec.size() << "\n";
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, stoll(arg), true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
}

void sobolevsky::getMax(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (vec.size() == 0)
  {
    throw std::exception();
  }
  if (arg == "AREA")
  {
    out << sobolevsky::getArea(*std::max_element(vec.cbegin(), vec.cend(), sobolevsky::getMaxMinArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << std::max_element(vec.cbegin(), vec.cend(), sobolevsky::getMaxMinVertex)->points.size() << "\n";
  }
}

void sobolevsky::getMin(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (vec.size() == 0)
  {
    throw std::exception();
  }
  if (arg == "AREA")
  {
    out << sobolevsky::getArea(*std::min_element(vec.cbegin(), vec.cend(), sobolevsky::getMaxMinArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    out << std::min_element(vec.cbegin(), vec.cend(), sobolevsky::getMaxMinVertex)->points.size() << "\n";
  }
}

void sobolevsky::count(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "EVEN")
  {
    using namespace std::placeholders;
    std::function< size_t(size_t, const sobolevsky::Polygon &) > bindVertEven = std::bind(sobolevsky::countIf, _1, _2, 0, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertEven) << "\n";
  }
  else if (arg == "ODD")
  {
    using namespace std::placeholders;
    std::function< size_t(size_t, const sobolevsky::Polygon &) > bindVertOdd = std::bind(sobolevsky::countIf, _1, _2, 1, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertOdd) << "\n";
  }
  else
  {
    if (stoll(arg) < 3)
    {
      throw std::exception();
    }
    using namespace std::placeholders;
    std::function< size_t(size_t, const sobolevsky::Polygon &) > bindVertNum = std::bind(sobolevsky::countIf, _1, _2, stoll(arg), true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertNum) << "\n";
  }
}

void sobolevsky::intersections(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  sobolevsky::Polygon inpPolyg;
  in >> inpPolyg;
  using namespace std::placeholders;
  std::function< bool(const sobolevsky::Polygon &) > bindIntersection = std::bind(sobolevsky::intersectPolyg, inpPolyg, _1);
  out << std::count_if(vec.cbegin(), vec.cend(), bindIntersection) << "\n";
}

void sobolevsky::same(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  sobolevsky::Polygon inpPolyg;
  in >> inpPolyg;
  using namespace std::placeholders;
  std::function< bool(const sobolevsky::Polygon &) > bindSame = std::bind(sobolevsky::isSamePolyg, inpPolyg, _1);
  out << std::count_if(vec.cbegin(), vec.cend(), bindSame) << "\n";
}
