#include <functional>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <iofmtguard.hpp>
#include <DelimiterIO.hpp>
#include "Commands.hpp"
#include "GeometryUtils.hpp"

void printInvalidCommand(std::ostream& output)
{
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);
  
  out << "<INVALID COMMAND>\n";
}

void areaCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    output << calculateAreaEvenOdd(true, polygons) << "\n";
  }
  else if (param == "ODD")
  {
    output << calculateAreaEvenOdd(false, polygons) << "\n";
  }
  else if (param == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid command");
    }
    output << calculateMeanArea(polygons) << "\n";
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
      output << calculateAreaByVertexCount(vertex_count, polygons) << "\n";
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("Invalid command");
    }
  }
}

void maxCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons)
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
    output << calculateMaxArea(polygons) << "\n";
  }
  else if (param == "VERTEXES")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid command");
    }
    output << calculateMaxVertexes(polygons) << "\n";
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void minCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "AREA")
  {
    output << calculateMinArea(polygons) << "\n";
  }
  else if (param == "VERTEXES")
  {
    output << calculateMinVertexes(polygons) << "\n";
  }
  else
  {
    throw std::invalid_argument("Invalid command");
  }
}

void countCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons)
{
  std::string param;
  input >> param;
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);

  if (param == "EVEN")
  {
    output << countPolygons(true, polygons) << "\n";
  }
  else if (param == "ODD")
  {
    output << countPolygons(false, polygons) << "\n";
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
      output << countPolygons(false, polygons, vertex_count) << "\n";
    }
    catch (const std::invalid_argument&)
    {
      throw std::invalid_argument("Invalid command");
    }
  }
}

void rmechoCommand(std::istream& input, std::ostream& output, std::vector< Polygon >& polygons)
{
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);
  
  int vertex_count;
  input >> vertex_count;
  Polygon target;
  target.points.resize(vertex_count);
  std::for_each(target.points.begin(), target.points.end(), [&input](Point& point)
  {
    char ignore;
    input >> DelimiterIO{ '(' } >> point.x >> ignore >> point.y >> DelimiterIO{ ')' };
  });
  output << removeEcho(target, polygons) << "\n";
}

void permsCommand(std::istream& input, std::ostream& output, const std::vector< Polygon >& polygons)
{
  iofmtguard guard(output);
  output << std::fixed << std::setprecision(1);
  
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
  output << countPerms(target, polygons) << "\n";
}
