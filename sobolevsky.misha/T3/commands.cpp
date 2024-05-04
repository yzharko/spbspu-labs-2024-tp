#include "commands.hpp"
#include <map>
#include <cctype>
#include <functional>
#include <numeric>
#include <algorithm>

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

bool sobolevsky::getMaxMinArea(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2, bool maxOrMin)
{
  if (maxOrMin)
  {
    return sobolevsky::getArea(polygon1) < sobolevsky::getArea(polygon2);
  }
  else
  {
    return sobolevsky::getArea(polygon1) > sobolevsky::getArea(polygon2);
  }
}

bool sobolevsky::getMaxMinVertex(const sobolevsky::Polygon & polygon1, const sobolevsky::Polygon & polygon2, bool maxOrMin)
{
  if (maxOrMin)
  {
    return polygon1.points.size() < polygon2.points.size();
  }
  else
  {
    return polygon1.points.size() > polygon2.points.size();
  }
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
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, 2, false);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) / vec.size() << "\n";
  }
  else
  {
    size_t num = stoll(arg);
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindareaIf = std::bind(sobolevsky::areaIf, _1, _2, num, true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindareaIf) << "\n";
  }
}

void sobolevsky::getMax(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "AREA")
  {
    using namespace std::placeholders;
    std::function< bool(const sobolevsky::Polygon &, const sobolevsky::Polygon &) > bindMaxArea = std::bind(sobolevsky::getMaxMinArea, _1, _2, true);
    out << sobolevsky::getArea(*std::max_element(vec.cbegin(), vec.cend(), bindMaxArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    using namespace std::placeholders;
    std::function< bool(const sobolevsky::Polygon &, const sobolevsky::Polygon &) > bindMaxVert = std::bind(sobolevsky::getMaxMinVertex, _1, _2, true);
    out << std::max_element(vec.cbegin(), vec.cend(), bindMaxVert)->points.size() << "\n";
  }
}

void sobolevsky::getMin(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  if (arg == "AREA")
  {
    using namespace std::placeholders;
    std::function< bool(const sobolevsky::Polygon &, const sobolevsky::Polygon &) > bindMaxArea = std::bind(sobolevsky::getMaxMinArea, _1, _2, false);
    out << sobolevsky::getArea(*std::max_element(vec.cbegin(), vec.cend(), bindMaxArea)) << "\n";
  }
  else if (arg == "VERTEXES")
  {
    using namespace std::placeholders;
    std::function< bool(const sobolevsky::Polygon &, const sobolevsky::Polygon &) > bindMaxVert = std::bind(sobolevsky::getMaxMinVertex, _1, _2, false);
    out << std::max_element(vec.cbegin(), vec.cend(), bindMaxVert)->points.size() << "\n";
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
    using namespace std::placeholders;
    std::function< size_t(size_t, const sobolevsky::Polygon &) > bindVertNum = std::bind(sobolevsky::countIf, _1, _2, stoll(arg), true);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0, bindVertNum) << "\n";
  }
}
