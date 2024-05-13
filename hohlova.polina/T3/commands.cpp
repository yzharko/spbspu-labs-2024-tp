#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>

bool hohlova::isValidFormat(const std::string& line, Polygon& polygon)
{
  std::istringstream iss(line);
  int num_points;
  char delim;
  if (!(iss >> num_points))
  {
    return false;
  }
  if (num_points < 3)
  {
    return false;
  }
  for (int i = 0; i < num_points; ++i)
  {
    Point point;
    if (!(iss >> delim >> point.x >> delim >> point.y >> delim))
    {
      return false;
    }
    polygon.points.push_back(point);
  }
  return true;
}

double hohlova::calcArea(const Polygon& polygon)
{
  double area = 0.0;
  int j = polygon.points.size() - 1;
  for (size_t i = 0; i < polygon.points.size(); ++i)
  {
    area += (polygon.points[j].x + polygon.points[i].x) * (polygon.points[j].y - polygon.points[i].y);
    j = i;
  }
  return std::abs(area) / 2.0;
}

int hohlova::countPerms(const Polygon& target, const std::vector<Polygon>& polygons)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    if (polygon.points.size() != target.points.size())
    {
      continue;
    }

    bool isPermutation = true;
    std::vector< bool > used(target.points.size(), false);

    for (const auto& point : polygon.points)
    {
      isPermutation = false;
      for (size_t i = 0; i < target.points.size(); ++i)
      {
        if (!used[i] && ((point.x == target.points[i].x && point.y == target.points[i].y) ||
        (point.x == target.points[i].y && point.y == target.points[i].x)))
        {
          used[i] = true;
          isPermutation = true;
          break;
        }
      }
      if (!isPermutation)
      {
        break;
      }
    }

    if (isPermutation)
    {
      count++;
    }
  }
  return count;
}

std::vector<Polygon> hohlova::readPolygonsFromFile(const std::string& filename)
{
  std::vector<Polygon> polygons;
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error: Unable to open file " << filename << "\n";
    return polygons;
  }
  std::string line;
  while (std::getline(file, line))
  {
    Polygon polygon;
    if (isValidFormat(line, polygon))
    {
      polygons.push_back(polygon);
    }
  }
  file.close();
  return polygons;
}

bool hohlova::comparePoints(const Point& a, const Point& b)
{
  if (a.x != b.x)
  {
    return a.x < b.x;
  }
  return a.y < b.y;
}

std::string hohlova::polygonToString(const Polygon& polygon)
{
  std::stringstream ss;
  std::vector<Point> sortedPoints(polygon.points);
  std::sort(sortedPoints.begin(), sortedPoints.end(), comparePoints);
  for (const auto& point : sortedPoints)
  {
    ss << "(" << point.x << ";" << point.y << ")";
  }
  return ss.str();
}

int hohlova::countVertices(const Polygon& polygon)
{
  return polygon.points.size();
}

void hohlova::processCommands(const std::vector<Polygon>& polygons)
{
  std::string command;
  while (true)
  {
    try
    {
      if (!(std::cin >> command))
      {
        if (std::cin.eof())
        {
          break;
        }
        throw std::runtime_error("Invalid command");
      }

      switch (command[0])
      {
      case 'A':
        if (command == "AREA")
        {
          std::string option;
          std::cin >> option;
          if (option == "MEAN")
          {
            double totalArea = 0.0;
            for (const auto& polygon : polygons)
            {
              totalArea += calcArea(polygon);
            }
            double meanArea = totalArea / polygons.size();
            std::cout << std::fixed << std::setprecision(1) << meanArea << "\n";
          }
          else if (option == "ODD" || option == "EVEN")
          {
            double totalArea = 0.0;
            for (const auto& polygon : polygons)
            {
              int numVertices = polygon.points.size();
              if ((option == "ODD" && numVertices % 2 != 0) ||
                (option == "EVEN" && numVertices % 2 == 0))
              {
                totalArea += calcArea(polygon);
              }
            }
            std::cout << std::fixed << std::setprecision(1) << totalArea << "\n";
          }
          else
          {
            unsigned long long numVertices = std::stoull(option);
            double totalArea = 0.0;
            for (const auto& polygon : polygons)
            {
              if (polygon.points.size() == numVertices)
              {
                totalArea += calcArea(polygon);
              }
            }
            std::cout << std::fixed << std::setprecision(1) << totalArea << "\n";
          }
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      case 'M':
        if (command == "MAX")
        {
          std::string option;
          std::cin >> option;
          double extremum = (option == "AREA") ? -std::numeric_limits<double>::infinity() : 0;
          bool found = false;
          for (const auto& polygon : polygons)
          {
            double value = (option == "AREA") ? calcArea(polygon) : polygon.points.size();
            if (value > extremum)
            {
              extremum = value;
              found = true;
            }
          }
          if (found)
          {
            std::cout << std::fixed << std::setprecision(1) << extremum << "\n";
          }
          else
          {
            std::cout << "No polygons found.\n";
          }
        }
        else if (command == "MIN")
        {
          std::string option;
          std::cin >> option;
          double extremum = (option == "AREA") ? std::numeric_limits<double>::infinity() : std::numeric_limits<int>::max();
          bool found = false;
          for (const auto& polygon : polygons)
          {
            double value = (option == "AREA") ? calcArea(polygon) : polygon.points.size();
            if (value < extremum)
            {
              extremum = value;
              found = true;
            }
          }
          if (found)
          {
            std::cout << std::fixed << std::setprecision(1) << extremum << "\n";
          }
          else
          {
            std::cout << "No polygons found.\n";
          }
        }
        else if (command == "MAXSEQ")
        {
          Polygon target;
          std::cin.ignore();
          std::string line;
          std::getline(std::cin, line);
          if (isValidFormat(line, target))
          {
            int count = countMaxSeq(target, polygons);
            std::cout << count << "\n";
          }
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      case 'C':
        if (command == "COUNT")
        {
          std::string option;
          std::cin >> option;
          int count = 0;
          if (option == "ODD" || option == "EVEN")
          {
            for (const auto& polygon : polygons)
            {
              int numVertices = polygon.points.size();
              if ((option == "ODD" && numVertices % 2 != 0) ||
                (option == "EVEN" && numVertices % 2 == 0))
              {
                count++;
              }
            }
            std::cout << count << "\n";
          }
          else
          {
            unsigned long long numVertices = std::stoull(option);
            for (const auto& polygon : polygons)
            {
              int polygonVertices = polygon.points.size();
              if (polygonVertices == numVertices)
              {
                count++;
              }
            }
            std::cout << count << "\n";
          }
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      case 'P':
        if (command == "PERMS")
        {
          Polygon target;
          std::cin.ignore();
          std::string line;
          std::getline(std::cin, line);
          if (isValidFormat(line, target))
          {
            int count = countPerms(target, polygons);
            std::cout << count << "\n";
          }
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      case 'R':
        if (command == "RIGHTSHAPES")
        {
          int count = countRightShapes(polygons);
          std::cout << count << "\n";
        }
        else
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      default:
        std::cout << "<INVALID COMMAND>\n";
        break;
      }
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}

int hohlova::countMaxSeq(const Polygon& target, const std::vector<Polygon>& polygons)
{
  int maxSeq = 0;
  int currentSeq = 0;
  for (const auto& polygon : polygons)
  {
    if (polygon.points.size() != target.points.size())
    {
      currentSeq = 0;
      continue;
    }
    bool match = true;
    for (size_t i = 0; i < target.points.size(); ++i)
    {
      if (polygon.points[i].x != target.points[i].x ||
        polygon.points[i].y != target.points[i].y)
      {
        match = false;
        break;
      }
    }
    if (match)
    {
      currentSeq++;
      maxSeq = std::max(maxSeq, currentSeq);
    }
    else
    {
      currentSeq = 0;
    }
  }
  return maxSeq;
}

int hohlova::countRightShapes(const std::vector<Polygon>& polygons)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    bool hasRightAngle = false;
    for (size_t i = 0; i < polygon.points.size(); ++i)
    {
      size_t j = (i + 1) % polygon.points.size();
      size_t k = (j + 1) % polygon.points.size();
      int dx1 = polygon.points[j].x - polygon.points[i].x;
      int dy1 = polygon.points[j].y - polygon.points[i].y;
      int dx2 = polygon.points[k].x - polygon.points[j].x;
      int dy2 = polygon.points[k].y - polygon.points[j].y;
      if (dx1 * dx2 + dy1 * dy2 == 0)
      {
        hasRightAngle = true;
        break;
      }
    }
    if (hasRightAngle)
    {
      count++;
    }
  }
  return count;
}
