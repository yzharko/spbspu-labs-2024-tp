#include <vector>
#include <string>
#include <functional>
#include <cctype>
#include <numeric>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <iofmtguard.hpp>
#include "comand.hpp"

namespace taskaev
{
  void AreaComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    std::string nameComand = "";
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
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygon.begin(), polygon.end(), 0.0, getAreaEven) << "\n";
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
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygon.begin(), polygon.end(), 0.0, getAreaOdd) << "\n";
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
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygon.begin(),polygon.end(), 0.0, getAreaSum) / static_cast< double >(polygon.size()) << "\n";
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
    using namespace std::placeholders;
    auto types = std::bind(getAreaNum, _1, _2, type);
    iofmtguard iofmtguard(out);
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(polygon.begin(), polygon.end(), 0.0, types) << "\n";
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
    std::string nameComand = "";
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
    std::string nameComand = "";
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
    std::string nameComand = "";
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
    in >> input;
    if ((polygon.empty()) || (in.fail()) || (input.points.size() < 3))
    {
      throw std::logic_error("");
    }
    iofmtguard iofmtguard(out);
    size_t countMaxSeq = 0;
    auto help = [&input](const Polygon& p)
    {
      return p == input;
    };
    auto iter = polygon.begin();
    while(iter != polygon.end())
    {
      auto count = std::count_if(iter, polygon.end(), help);
      countMaxSeq = std::max(countMaxSeq, static_cast< size_t >(count));
      iter += count;
    }
    if (countMaxSeq == 0)
    {
      throw std::logic_error("");
    }
    out << countMaxSeq << "\n";
  }
  void SameComand(const std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
  {
    Polygon input;
    in >> input;
    if (in.fail())
    {
      throw std::logic_error("");
    }
    iofmtguard iofmtguard(out);
    using namespace std::placeholders;
    auto function = std::bind(polygonSame, _1, input);
    if (std::count_if(polygon.begin(), polygon.end(), function) == 0)
    {
      throw std::logic_error("");
    }
    out << std::count_if(polygon.begin(), polygon.end(), function) << "\n";
  }
  bool polygonSame(const Polygon& polygonOne, const Polygon& polygonTwo)
  {
    if (polygonOne.points.size() == polygonTwo.points.size())
    {
      Polygon movedPolygonOne = movePolygon(polygonOne);
      Polygon movedPolygonTwo = movePolygon(polygonTwo);
      bool  flag = std::equal(
        movedPolygonOne.points.begin(),
        movedPolygonOne.points.end(),
        movedPolygonTwo.points.begin(),
        PointPolygon
      );
      return flag;
    }
    else
    {
      return false;
    }
  }
  bool PointPolygon(const Point& left, const Point& right)
  {
    return left.x_ == right.x_ && left.y_ == right.y_;
  }
  Polygon movePolygon(const Polygon& polygon)
  {
    std::vector< Point > position(polygon.points.size());
    using namespace std::placeholders;
    auto a = std::bind(delta, _1, polygon.points.front().x_, polygon.points.front().y_);
    std::transform(polygon.points.begin(), polygon.points.end(), std::back_inserter(position), a);
    return Polygon{position};
  }
  Point delta(const Point& point, int X, int Y)
  {
    return {point.x_ - X, point.y_ - Y};
  }

  void invalidMessage(std::ostream& out, const std::string& text)
  {
    iofmtguard iofmtguard(out);
    out << text;
  }
}
