#include "commands.hpp"
#include <map>
#include <cctype>
#include <functional>
#include <numeric>

double sobolevsky::AreaIf(double result, const sobolevsky::Polygon & polygon, size_t mode)
{
  if (mode == 2)
  {
    result += sobolevsky::getArea(polygon);
  }
  else if (mode == (polygon.points.size() % 2))
  {
    result += sobolevsky::getArea(polygon);
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
    std::function< double(double, const sobolevsky::Polygon &) > bindAreaIf = std::bind(sobolevsky::AreaIf, _1, _2, 0);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindAreaIf) << "\n";
  }
  else if (arg == "ODD")
  {
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindAreaIf = std::bind(sobolevsky::AreaIf, _1, _2, 1);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindAreaIf) << "\n";
  }
  else if (arg == "MEAN")
  {
    using namespace std::placeholders;
    std::function< double(double, const sobolevsky::Polygon &) > bindAreaIf = std::bind(sobolevsky::AreaIf, _1, _2, 2);
    out << std::accumulate(vec.cbegin(), vec.cend(), 0.0, bindAreaIf) / vec.size() << "\n";
  }
  else
  {

  }
}

void sobolevsky::max(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "max\n";
}

void sobolevsky::min(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "min\n";
}

void sobolevsky::count(const std::vector< sobolevsky::Polygon > & vec, std::istream & in, std::ostream & out)
{
  out << "count\n";
}
