#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>
#include <iosfwd>
#include <limits>
#include <stdexcept>
#include <DelimiterIO.hpp>
#include <iofmtguard.hpp>
#include "Commands.hpp"
#include "GeometryUtils.hpp"

Commands::Commands(std::vector< Polygon >& polygons) : polygons(polygons)
{}

void Commands::areaCommand(std::istream& input, std::ostream& output)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    output << calculateAreaEvenOdd(true) << "\n";
  }
  else if (param == "ODD")
  {
    output << calculateAreaEvenOdd(false) << "\n";
  }
  else if (param == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid command");
    }
    output << calculateMeanArea() << "\n";
  }
  else
  {
    try
    {
      int vertex_count = std::stoi(param);
      if (vertex_count < 3)
      {
        throw std::invalid_argument("Invalid vertex count");
      }
      output << calculateAreaByVertexCount(vertex_count) << "\n";
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("Invalid command");
    }
  }
}

void Commands::maxCommand(std::istream& input, std::ostream& output)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "AREA")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid command");
    }
    output << calculateMaxArea() << "\n";
  }
  else if (param == "VERTEXES")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid command");
    }
    output << calculateMaxVertexes() << "\n";
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void Commands::minCommand(std::istream& input, std::ostream& output)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "AREA")
  {
    output << calculateMinArea() << "\n";
  }
  else if (param == "VERTEXES")
  {
    output << calculateMinVertexes() << "\n";
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void Commands::countCommand(std::istream& input, std::ostream& output)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    output << countPolygons(true) << "\n";
  }
  else if (param == "ODD")
  {
    output << countPolygons(false) << "\n";
  }
  else
  {
    try
    {
      int vertex_count = std::stoi(param);
      if (vertex_count < 3)
      {
        throw std::invalid_argument("Invalid vertex count");
      }
      output << countPolygons(false, vertex_count) << "\n";
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("Invalid command");
    }
  }
}

void Commands::rmechoCommand(std::istream& input, std::ostream& output)
{
  int vertex_count;
  input >> vertex_count;
  Polygon target;
  target.points.resize(vertex_count);
  std::for_each(target.points.begin(), target.points.end(), [&input](Point& point)
  {
    char ignore;
    input >> DelimiterIO{ '(' } >> point.x >> ignore >> point.y >> DelimiterIO{ ')' };
  });
  output << removeEcho(target) << "\n";
}

void Commands::permsCommand(std::istream& input, std::ostream& output)
{
  int vertex_count;
  input >> vertex_count;
  if (vertex_count < 3)
  {
    throw std::invalid_argument("Invalid command");
  }

  Polygon target;
  target.points.resize(vertex_count);
  std::for_each(target.points.begin(), target.points.end(), [&input](Point& point)
  {
    char ignore;
    input >> DelimiterIO{ '(' } >> point.x >> ignore >> point.y >> DelimiterIO{ ')' };
  });
  output << countPerms(target) << "\n";
}

double Commands::calculateAreaEvenOdd(bool even) const
{
  auto isEvenOdd = [even](const Polygon& polygon)
  {
    return (polygon.points.size() % 2 == 0) == even;
  };
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, [&](double sum, const Polygon& polygon)
  {
    return sum + (isEvenOdd(polygon) ? GeometryUtils().calculateArea(polygon) : 0.0);
  });
}

double Commands::calculateMeanArea() const
{
  double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double sum, const Polygon& polygon)
  {
    return sum + GeometryUtils().calculateArea(polygon);
  });
  return polygons.empty() ? 0.0 : totalArea / polygons.size();
}

double Commands::calculateAreaByVertexCount(int count) const
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0, [count](double sum, const Polygon& polygon)
  {
    return sum
        + (polygon.points.size() == static_cast<std::vector< Point >::size_type>(count) ? GeometryUtils().calculateArea(
            polygon) : 0.0);
  });
}

double Commands::calculateMaxArea() const
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return GeometryUtils().calculateArea(a) < GeometryUtils().calculateArea(b);
  });
  return maxElement != polygons.end() ? GeometryUtils().calculateArea(*maxElement) : 0.0;
}

int Commands::calculateMaxVertexes() const
{
  auto maxElement = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return maxElement != polygons.end() ? maxElement->points.size() : 0;
}

double Commands::calculateMinArea() const
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return GeometryUtils().calculateArea(a) < GeometryUtils().calculateArea(b);
  });
  return minElement != polygons.end() ? GeometryUtils().calculateArea(*minElement) : 0.0;
}

int Commands::calculateMinVertexes() const
{
  auto minElement = std::min_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  });
  return minElement != polygons.end() ? minElement->points.size() : 0;
}

int Commands::countPolygons(bool even, int vertex_count) const
{
  if (vertex_count != -1)
  {
    return std::count_if(polygons.begin(), polygons.end(), [vertex_count](const Polygon& polygon)
    {
      return polygon.points.size() == static_cast<std::vector< Point >::size_type>(vertex_count);
    });
  }
  else
  {
    return std::count_if(polygons.begin(), polygons.end(), [even](const Polygon& polygon)
    {
      return (polygon.points.size() % 2 == 0) == even;
    });
  }
}

int Commands::countPerms(const Polygon& target) const
{
  auto arePermutations = [](const std::vector< Point >& a, const std::vector< Point >& b)
  {
    if (a.size() != b.size())
    {
      return false;
    }

    std::vector< Point > sortedA = a;
    std::vector< Point > sortedB = b;

    auto pointComp = [](const Point& p1, const Point& p2)
    {
      return (p1.x == p2.x) ? (p1.y < p2.y) : (p1.x < p2.x);
    };

    std::sort(sortedA.begin(), sortedA.end(), pointComp);
    std::sort(sortedB.begin(), sortedB.end(), pointComp);

    auto comparePoints = [](const Point& a, const Point& b)
    {
      return (a.x == b.x && a.y == b.y) || (a.x == b.y && a.y == b.x);
    };

    return std::equal(sortedA.begin(), sortedA.end(), sortedB.begin(), comparePoints);
  };

  return std::count_if(polygons.begin(), polygons.end(), [&](const Polygon& polygon)
  {
    return arePermutations(polygon.points, target.points);
  });
}

int Commands::removeEcho(const Polygon& target)
{
  auto isDuplicate = [&](const Polygon& a, const Polygon& b)
  {
    return a == b && a == target;
  };

  auto removeIt = std::unique(polygons.begin(), polygons.end(), isDuplicate);
  int removeCount = std::distance(removeIt, polygons.end());
  polygons.erase(removeIt, polygons.end());
  return removeCount;
}
