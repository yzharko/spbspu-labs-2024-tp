#include "Commands.hpp"
#include <cmath>
#include <numeric>
#include <functional>
#include <iomanip>
#include <algorithm>
#include "Iofmtguard.hpp"

using namespace std::placeholders;
namespace proselkov
{
  double areaHelper(const Point& point1, const  Point& point2)
  {
    return (point1.x * point2.y - point1.y * point2.x);
  }
  double getArea(const Polygon& shape)
  {
    auto pointTemp = ++shape.points.begin();
    double area = std::accumulate(shape.points.begin(), --shape.points.end(), 0.0,
      [&pointTemp](double areaTemp, const Point& point)
      {
        areaTemp += areaHelper(point, *pointTemp);
        pointTemp++;
        return areaTemp;
      });
    area += areaHelper(*--shape.points.end(), *shape.points.begin());
    return std::fabs(area / 2.0);
  }
  double addArea(double area, const Polygon& shape, std::function< bool(const Polygon&) > exp)
  {
    return area += (exp(shape) ? getArea(shape) : 0);
  }
  double addEveryArea(double area, const Polygon& shape)
  {
    return area += getArea(shape);
  }
  bool hasOddPoints(const Polygon& shape)
  {
    return shape.points.size() % 2 != 0;
  }
  bool hasEvenPoints(const Polygon& shape)
  {
    return !hasOddPoints(shape);
  }
  bool hasNumOfPoints(const Polygon& shape, size_t size)
  {
    return shape.points.size() == size;
  }
  std::ostream& area(std::istream& in, std::ostream& out, std::vector< Polygon >& shapes)
  {
    out << std::fixed << std::setprecision(1);
    std::string arg;
    in >> arg;
    Iofmtguard fmtguard(out);
    if (arg == "ODD")
    {
      auto functor = std::bind(addArea, _1, _2, hasOddPoints);
      return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
    }
    else if (arg == "EVEN")
    {
      auto functor = std::bind(addArea, _1, _2, hasEvenPoints);
      return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
    }
    else if (arg == "MEAN")
    {
      if (shapes.size() == 0)
      {
        throw std::invalid_argument("");
      }
      auto functor = std::bind(addEveryArea, _1, _2);
      return out << std::accumulate(shapes.begin(), shapes.end(),
        0.0, functor) / shapes.size() << '\n';
    }
    else
    {
      size_t size = std::stoull(arg);
      if (size <= 2)
      {
        throw std::invalid_argument("");
      }
      std::function< bool(const Polygon&) > temp = std::bind(hasNumOfPoints, _1, size);
      auto functor = std::bind(addArea, _1, _2, temp);
      return out << std::accumulate(shapes.begin(), shapes.end(), 0.0, functor) << '\n';
    }
  }
  bool comparedArea(const Polygon& shape1, const Polygon& shape2)
  {
    return (getArea(shape1) < getArea(shape2));
  }
  size_t comparedVert(const Polygon& shape1, const Polygon& shape2)
  {
    return shape1.points.size() < shape2.points.size();
  }
  bool isRect(const Polygon& shape)
  {
    if (shape.points.size() != 4)
    {
      return false;
    }
    std::vector<Point> vectors;
    for (int i = 0; i < 4; i++)
    {
      for (int j = i + 1; j < 4; j++)
      {
        vectors.push_back(Point{ shape.points[j].x - shape.points[i].x, shape.points[j].y - shape.points[i].y });
      }
    }
    std::vector<Point> newVectors;
    for (int i = 0; i < 6; i++)
    {
      for (int j = i + 1; j < 6; j++)
      {
        if ((vectors[i].x == vectors[j].x && vectors[i].y == vectors[j].y) || (vectors[i].x == -vectors[j].x && vectors[i].y == -vectors[j].y)) {
          newVectors.push_back(vectors[i]);
        }
      }
    }
    if (newVectors.size() != 2 || (newVectors[0].x * newVectors[1].x + newVectors[0].y * newVectors[1].y) != 0)
    {
      return false;
    }
    return true;
  }
  std::ostream& max(std::istream& in, std::ostream& out,
    std::vector< Polygon >& shapes)
  {
    Iofmtguard fmtguard(out);
    std::string arg;
    in >> arg;

    if (!shapes.empty() && arg == "AREA")
    {
      out << std::fixed << std::setprecision(1);
      auto maxEl = std::max_element(shapes.begin(), shapes.end(), comparedArea);
      return out << getArea(*maxEl) << '\n';
    }
    else if (!shapes.empty() && arg == "VERTEXES")
    {
      auto maxEl = std::max_element(shapes.begin(), shapes.end(), comparedVert);
      return out << maxEl->points.size() << '\n';
    }
    else
    {
      throw std::invalid_argument("");
    }
  }
  std::ostream& min(std::istream& in, std::ostream& out,
    std::vector< Polygon >& shapes)
  {
    std::string arg;
    in >> arg;
    Iofmtguard fmtguard(out);
    if (!shapes.empty() && arg == "AREA")
    {
      out << std::fixed << std::setprecision(1);
      auto minEl = std::min_element(shapes.begin(), shapes.end(), comparedArea);
      return out << getArea(*minEl) << '\n';
    }
    else if (!shapes.empty() && arg == "VERTEXES")
    {
      auto minEl = std::min_element(shapes.begin(), shapes.end(), comparedVert);
      return out << minEl->points.size() << '\n';
    }
    else
    {
      throw std::invalid_argument("");
    }
  }
  std::ostream& count(std::istream& in, std::ostream& out,
    std::vector< Polygon >& shapes)
  {
    std::string arg;
    in >> arg;
    Iofmtguard fmtguard(out);
    if (arg == "ODD")
    {
      return out << std::count_if(shapes.begin(), shapes.end(), hasOddPoints) << '\n';
    }
    else if (arg == "EVEN")
    {
      return out << std::count_if(shapes.begin(), shapes.end(), hasEvenPoints) << '\n';
    }
    else
    {
      size_t size = std::stoull(arg);
      if (size <= 2)
      {
        throw std::invalid_argument("");
      }
      auto functor = std::bind(hasNumOfPoints, _1, size);
      return out << std::count_if(shapes.begin(), shapes.end(), functor) << '\n';
    }
  }

  std::ostream& rects(std::istream& in, std::ostream& out,
    std::vector< Polygon >& shapes)
  {
    auto functor = std::bind(isRect, _1);
    return out << std::count_if(shapes.begin(), shapes.end(), functor) << '\n';
  }

  std::ostream& rmecho(std::istream& in, std::ostream& out,
    std::vector< Polygon >& shapes)
  {
    Polygon arg;
    in >> arg;
    Iofmtguard fmtguard(out);
    if (in.fail())
    {
      throw std::invalid_argument("");
    }
    size_t res = 0;
    bool toDelete = false;
    for (int i = 0; i < shapes.size(); i++)
    {
      if (shapes[i] == arg)
      {
        if (toDelete)
        {
          res++;
          shapes.erase(shapes.begin() + i);
        }
        else
        {
          toDelete = true;
        }
      }
      else
      {
        toDelete = false;
      }
    }
    return out << res << '\n';
  }
}
