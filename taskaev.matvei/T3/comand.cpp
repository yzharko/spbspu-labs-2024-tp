#include <vector>
#include <string>
#include <functional>
#include <cctype>
#include <numeric>
#include <utility>
#include <iomanip>
#include <algorithm>
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
      throw std::logic_error("");
    }
  }

  size_t countVertexes(const Polygon& polygon)
  {
    return polygon.points.size();
  }

  double getAreas(const Point& pointOne, const Point& pointTwo)
  {
    return ( pointOne.x_ * pointTwo.y_ ) - ( pointTwo.x_ * pointOne.y_ );
  }

  double getArea(const Polygon& polygon)
  {
    std::vector< double > area(polygon.points.size());
    using namespace  std::placeholders;
    std::transform(
      ++(polygon.points.begin()),
      polygon.points.end(),
      polygon.points.begin(),
      area.begin(),
      std::bind(getAreas, _1, _2)
    );

    double sum = std::accumulate(area.begin(), area.end(), 0.0);
    sum += getAreas(polygon.points.front(), polygon.points.back());

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
    out << std::fixed << std::setprecision(1) << area << "\n";
  }
  double getAreaEven(double area, const Polygon& polygon)
  {
    if ((polygon.points.size() % 2 == 0))
    {
      return area + getArea(polygon);
    }
    else
    {
      return area;
    }
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
    out << std::fixed << std::setprecision(1) << area << "\n";
  }
  double getAreaOdd(double area, const Polygon& polygon)
  {
    if (!(polygon.points.size() % 2 == 0))
    {
      return area + getArea(polygon);
    }
    else
    {
      return area;
    }
  }

  void AreaMean(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (polygon.empty())
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
    out << std::fixed << std::setprecision(1) << meanArea << "\n";
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
    out << std::fixed << std::setprecision(1) << area << "\n";
  }
  double getAreaNum(double area, const Polygon& polygon, size_t type)
  {
    if (countVertexes(polygon) != type)
    {
      return area;
    }
    return area + getArea(polygon);
  }


  void MaxComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand;
    if (in >> nameComand)
    {
      if (nameComand == "AREA")
      {
        MaxArea(polygon, out);
      }
      else if (nameComand == "VERTEXES")
      {
        MaxVertexes(polygon, out);
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }
  void MaxArea(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (polygon.empty())
    {
      throw std::logic_error("");
    }
    std::vector< double > area(polygon.size());
    std::transform(polygon.begin(), polygon.end(), area.begin(), getArea);
    auto AreaIter = std::max_element(area.begin(), area.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << *AreaIter << "\n";
  }
  void MaxVertexes(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (polygon.empty())
    {
      throw std::logic_error("");
    }
    std::vector< size_t > vertexes(polygon.size());
    std::transform(polygon.begin(), polygon.end(), vertexes.begin(), countVertexes);
    auto VertexesIter = std::max_element(vertexes.begin(), vertexes.end());
    out << *VertexesIter << "\n";
  }

  void MinComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand;
    if (in >> nameComand)
    {
      if (nameComand == "AREA")
      {
        minArea(polygon, out);
      }
      else if (nameComand == "VERTEXES")
      {
        minVertexes(polygon, out);
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void minArea(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (polygon.empty())
    {
      throw std::logic_error("");
    }
    std::vector< double > area(polygon.size());
    std::transform(polygon.begin(), polygon.end(), area.begin(), getArea);
    auto AreaIter = std::min_element(area.begin(), area.end());
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << *AreaIter << "\n";
  }

  void minVertexes(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    if (polygon.empty())
    {
      throw std::logic_error("");
    }
    std::vector< size_t > vertexes(polygon.size());
    std::transform(polygon.begin(), polygon.end(), vertexes.begin(), countVertexes);
    auto VertexesIter = std::min_element(vertexes.begin(), vertexes.end());
    out << *VertexesIter << "\n";
  }

  void CountComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand;
    if (in >> nameComand)
    {
      if (nameComand == "EVEN")
      {
        EvenCount(polygon, out);
      }
      else if (nameComand == "ODD")
      {
        OddCount(polygon, out);
      }
      else
      {
        size_t type = std::stoull(nameComand);
        VertexesCount(polygon, out, type);
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  bool EvenVertexes(const Polygon& polygon)
  {
    return !OddVertexes(polygon);
  }
  bool OddVertexes(const Polygon& polygon)
  {
    return countVertexes(polygon) % 2;
  }
  void EvenCount(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    size_t countEven = std::count_if(polygon.begin(), polygon.end(), EvenVertexes);
    out << countEven << "\n";
  }
  void OddCount(const std::vector< Polygon >& polygon, std::ostream& out)
  {
    size_t countOdd = std::count_if(polygon.begin(), polygon.end(), OddVertexes);
    out << countOdd << "\n";
  }
  bool Vertexes(const Polygon& polygon, size_t type)
  {
    return polygon.points.size() == type;
  }
  void VertexesCount(const std::vector< Polygon >& polygon, std::ostream& out, size_t type)
  {
    if (type < 3)
    {
      throw std::logic_error("");
    }
    auto helps = std::bind(Vertexes, std::placeholders::_1, type);
    auto counts = std::count_if(polygon.begin(), polygon.end(), helps);
    out << counts << "\n";
  }

  void MaxSeqComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    Polygon input;
    if (!(in >> input))
    {
      throw std::logic_error("");
    }
    size_t countMaxSeq = 0;
    auto help = [&input](const Polygon& p)
    {
      return p == input;
    };
    auto iter = polygon.begin();
    while ( iter != polygon.end())
    {
      auto count = std::count_if(iter, polygon.end(), help);
      countMaxSeq = std::max(countMaxSeq, static_cast< size_t >(count));
      iter += count;
    }
    out << countMaxSeq << "\n";
  }
}
