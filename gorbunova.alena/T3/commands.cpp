#include <iomanip>
#include <algorithm>
#include <numeric>
#include "commands.hpp"

namespace gorbunova
{
  std::ostream &areaCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons)
  {
    std::string arg;
    input >> arg;
    if (arg == "EVEN")
    {
      double areaSum = calculateAreaSum(polygons, [](const Polygon &p)
      { return p.points.size() % 2 == 0; });
      output << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
    else if (arg == "ODD")
    {
      double areaSum = calculateAreaSum(polygons, [](const Polygon &p)
      { return p.points.size() % 2 != 0; });
      output << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
    else if (arg == "MEAN")
    {
      if (polygons.empty())
      {
        output << "0.0" << std::endl;
        return output;
      }
      double totalArea = calculateAreaSum(polygons, [](const Polygon &p)
      { return true; });
      double meanArea = totalArea / polygons.size();
      output << std::fixed << std::setprecision(1) << meanArea << std::endl;
    }
    else
    {
      size_t num_vertices = std::stoi(arg);
      double areaSum = calculateAreaSum(polygons, [num_vertices](const Polygon &p)
      { return p.points.size() == num_vertices; });
      output << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
    return output;
  }

  std::ostream &maxCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons)
  {
    std::string arg;
    input >> arg;
    if (arg == "AREA")
    {
      auto max_it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.calculateArea() < p2.calculateArea();
        });
        output << std::fixed << std::setprecision(1) << max_it->calculateArea() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
      auto max_it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.points.size() < p2.points.size();
        });
        output << max_it->points.size() << std::endl;
    }
    return output;
  }

  std::ostream &minCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons)
  {
    std::string arg;
    input >> arg;
    if (arg == "AREA")
    {
      auto min_it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.calculateArea() < p2.calculateArea();
        });
        output << std::fixed << std::setprecision(1) << min_it->calculateArea() << std::endl;
      }
      else if (arg == "VERTEXES")
      {
        auto min_it = std::min_element(polygons.begin(), polygons.end(),
          [](const Polygon &p1, const Polygon &p2)
          {
            return p1.points.size() < p2.points.size();
          });
          output << min_it->points.size() << std::endl;
      }
      return output;
  }

  std::ostream &countCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons)
  {
    std::string arg;
    input >> arg;
    if (arg == "EVEN")
    {
      size_t count = countPolygons(polygons, [](const Polygon &p)
      { return p.points.size() % 2 == 0; });
      output << count << std::endl;
    }
    else if (arg == "ODD")
    {
      size_t count = countPolygons(polygons, [](const Polygon &p)
      { return p.points.size() % 2 != 0; });
      output << count << std::endl;
    }
    else
    {
      size_t num_vertices = std::stoi(arg);
      size_t count = countPolygons(polygons, [num_vertices](const Polygon &p)
      { return p.points.size() == num_vertices; });
      output << count << std::endl;
    }
    return output;
  }

  std::ostream &maxseqCommand(std::istream &input, std::ostream &output, const std::vector< Polygon > &polygons)
  {
    Polygon target = parsePolygonFromCommand(input);
    size_t max_seq = std::accumulate(polygons.begin(), polygons.end(), 0,
      [&target](size_t maxSeq, const Polygon &p)
      {
        static size_t currentSeq = 0;
        if (p == target)
        {
          ++currentSeq;
          maxSeq = std::max(maxSeq, currentSeq);
        }
        else
        {
          currentSeq = 0;
        }
        return maxSeq;
      });
      output << max_seq << std::endl;
      return output;
  }

  std::ostream &echoCommand(std::istream &input, std::ostream &output, std::vector< Polygon > &polygons)
  {
    Polygon target = parsePolygonFromCommand(input);
    size_t added_count = 0;
    auto it = polygons.begin();
    while ((it = std::find(it, polygons.end(), target)) != polygons.end())
    {
      it = polygons.insert(it + 1, target);
      ++added_count;
      ++it;
    }
    output << added_count << std::endl;
    return output;
  }
}
