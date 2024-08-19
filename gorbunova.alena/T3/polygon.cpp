#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <functional>
#include "polygon.hpp"

bool Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool Polygon::operator==(const Polygon &other) const
{
  return points == other.points;
}

double Polygon::calculateArea() const
{
  int n = points.size();
  if (n < 3)
    return 0.0;
  std::vector<double> x_terms(n);
  std::vector<double> y_terms(n);
  std::transform(points.begin(), points.end(), x_terms.begin(),
    [](const Point &p) { return static_cast<double>(p.x); });
  std::transform(points.begin(), points.end(), y_terms.begin(),
    [](const Point &p) { return static_cast<double>(p.y); });
  x_terms.push_back(x_terms[0]);
  y_terms.push_back(y_terms[0]);
  double area = std::inner_product(x_terms.begin(), x_terms.end() - 1,
                                   y_terms.begin() + 1, 0.0) -
                std::inner_product(y_terms.begin(), y_terms.end() - 1,
                                   x_terms.begin() + 1, 0.0);
  return std::abs(area) / 2.0;
}

std::vector<Polygon> readPolygonsFromFile(const std::string &filename)
{
  std::ifstream file(filename);
  std::vector<Polygon> polygons;
  if (!file.is_open())
  {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return polygons;
  }
  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    int num_points;
    if (!(iss >> num_points))
    {
      continue;
    }
    Polygon polygon;
    polygon.points.reserve(num_points);
    std::generate_n(std::back_inserter(polygon.points), num_points, [&iss]()
    {
      Point p;
      char ignore_char;
      iss >> ignore_char >> p.x >> ignore_char >> p.y >> ignore_char;
      return p; });
    polygons.push_back(polygon);
  }
  return polygons;
}

double calculateAreaSum(const std::vector<Polygon> &polygons, std::function<bool(const Polygon &)> filter)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [filter](double sum, const Polygon &p)
    {
      return filter(p) ? sum + p.calculateArea() : sum;
    });
}

int countPolygons(const std::vector<Polygon> &polygons, std::function<bool(const Polygon &)> filter)
{
  return std::count_if(polygons.begin(), polygons.end(), filter);
}

Polygon parsePolygonFromCommand(std::istringstream &iss)
{
  Polygon polygon;
  int num_points;
  iss >> num_points;
  polygon.points.reserve(num_points);
  std::generate_n(std::back_inserter(polygon.points), num_points, [&iss]()
  {
    Point p;
    char ignore_char;
    iss >> ignore_char >> p.x >> ignore_char >> p.y >> ignore_char;
    return p; });
  return polygon;
}

void processCommand(const std::string &command, std::vector<Polygon> &polygons)
{
  std::istringstream iss(command);
  std::string cmd;
  iss >> cmd;
  if (cmd == "AREA")
  {
    std::string arg;
    iss >> arg;
    if (arg == "EVEN")
    {
      double areaSum = calculateAreaSum(polygons, [](const Polygon &p)
      { return p.points.size() % 2 == 0; });
      std::cout << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
    else if (arg == "ODD")
    {
      double areaSum = calculateAreaSum(polygons, [](const Polygon &p)
      { return p.points.size() % 2 != 0; });
      std::cout << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
    else if (arg == "MEAN")
    {
      if (polygons.empty())
      {
        std::cout << "0.0" << std::endl;
        return;
      }
      double totalArea = calculateAreaSum(polygons, [](const Polygon &p)
      { return true; });
      double meanArea = totalArea / polygons.size();
      std::cout << std::fixed << std::setprecision(1) << meanArea << std::endl;
    }
    else
    {
      int num_vertices = std::stoi(arg);
      double areaSum = calculateAreaSum(polygons, [num_vertices](const Polygon &p)
      { return p.points.size() == num_vertices; });
      std::cout << std::fixed << std::setprecision(1) << areaSum << std::endl;
    }
  }
  else if (cmd == "COUNT")
  {
    std::string arg;
    iss >> arg;
    if (arg == "EVEN")
    {
      int count = countPolygons(polygons, [](const Polygon &p)
      { return p.points.size() % 2 == 0; });
      std::cout << count << std::endl;
    }
    else if (arg == "ODD")
    {
      int count = countPolygons(polygons, [](const Polygon &p)
      { return p.points.size() % 2 != 0; });
      std::cout << count << std::endl;
    }
    else
    {
      int num_vertices = std::stoi(arg);
      int count = countPolygons(polygons, [num_vertices](const Polygon &p)
      { return p.points.size() == num_vertices; });
      std::cout << count << std::endl;
    }
  }
  else if (cmd == "MAX")
  {
    std::string arg;
    iss >> arg;
    if (arg == "AREA")
    {
      auto max_it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.calculateArea() < p2.calculateArea();
        });
        std::cout << std::fixed << std::setprecision(1) << max_it->calculateArea() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
      auto max_it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.points.size() < p2.points.size();
        });
        std::cout << max_it->points.size() << std::endl;
    }
  }
  else if (cmd == "MIN")
  {
    std::string arg;
    iss >> arg;
    if (arg == "AREA")
    {
      auto min_it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.calculateArea() < p2.calculateArea();
        });
        std::cout << std::fixed << std::setprecision(1) << min_it->calculateArea() << std::endl;
    }
    else if (arg == "VERTEXES")
    {
      auto min_it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon &p1, const Polygon &p2)
        {
          return p1.points.size() < p2.points.size();
        });
        std::cout << min_it->points.size() << std::endl;
    }
  }
  else if (cmd == "MAXSEQ")
  {
    Polygon target = parsePolygonFromCommand(iss);
    int max_seq = std::accumulate(polygons.begin(), polygons.end(), 0,
      [&target](int maxSeq, const Polygon &p)
      {
        static int currentSeq = 0;
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
    std::cout << max_seq << std::endl;
  }
  else if (cmd == "ECHO")
  {
    Polygon target = parsePolygonFromCommand(iss);
    int added_count = 0;
    auto it = polygons.begin();
    while ((it = std::find(it, polygons.end(), target)) != polygons.end())
    {
      it = polygons.insert(it + 1, target);
      ++added_count;
      ++it;
    }
    std::cout << added_count << std::endl;
  }
  else
  {
    std::cout << "<INVALID COMMAND>" << std::endl;
  }
}
