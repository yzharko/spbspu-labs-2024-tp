#include <vector>
#include <string>
#include <iomanip>
#include "iofmtguard.hpp"
#include "comand.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand;
    if (in >> nameComand)
    {
      if (nameComand == "EVEN")
      {
        AreaEven(polygon, out);
      }
      else if (nameComand == "ODD")
      {
        AreaOdd(polygon, out);
      }
      else if (nameComand == "MEAN")
      {
        AreaMean(polygon, out);
      }
      else
      {
        size_t type = std::stoull(nameComand);
        AreaNum(polygon, out, type);
      }
    }
    else
    {
      throw std::logic_error("<INVALID COMAND>\n");
    }
  }

  double getAreas(const Point& point1, const Point& point2)
  {
    return point1.x * point2.y - point2.x * point1.y;
  }

  double getArea(const Polygon& polygon)
  {
    std::vector< double > area(polygon.points.size());

    std::transform(
      polygon.points.begin(),
      polygon.points.end() - 1,
      polygon.points.begin() + 1,
      area.begin(),
      getAreas
    );

    double sum = std::accumulate(area.begin(), area.end(), 0.0);
    sum += getAreaS(polygon.points.back(), polygon.points.front());

    return 0.5 * std::abs(sum);
  }

  void AreaEven(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    double area = std::accumulate(
      polygon.begin(),
      polygon.end(),
      0.0,
      getAreaEven
    );
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  double getAreaEven(double area, const Polygon& polygon)
  {
    if ((polygon.points.size() % 2 == 0))
    {
      return area;
    }
    return area + getArea(polygon);
  }

  void AreaOdd(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    double area = std::accumulate(
      polygon.begin(),
      polygon.end(),
      0.0,
      getAreaOdd
    );
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  double getAreaOdd(double area, const Polygon& polygon)
  {
    if (!(polygon.points.size()%2 == 0))
    {
      return area;
    }
    return area + getArea(polygon);
  }

  void AreaMean(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }

    double area = std::accumulate(
      polygon.begin(),
      polygon.end(),
      0.0,
      getAreaSum
    );

    double meanArea = area / static_cast< double >(polygon.size());

    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << meanArea << '\n';
  }
  double getAreaSum(double area, const Polygon& polygon)
  {
    return area + getArea(polygon);
  }

  void AreaNum(const std::vector< Polygon >& polygon, std::ostream& out, size_t type)
  {
    if (type < 3)
    {
      throw std::logic_error("");
    }
    auto types = std::bind(
      getAreaNum,
      std::placeholders::_1,
      std::placeholders::_2,
      type
    );
    double area = std::accumulate(
      polygon.begin(),
      polygon.end(),
      0.0,
      types
    );
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  double getAreaNum(double area, const Polygon& polygon, size_t type)
  {
    if (polygon.points.size() != type)
    {
      return area;
    }
    return area + getArea(polygon);
  }
}
