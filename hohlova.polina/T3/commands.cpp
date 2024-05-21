#include "commands.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <functional>

void hohlova::Error(std::ostream& out)
{
  std::cout << "<INVALID COMMAND>\n";
}

double hohlova::CalcArea(const Polygon& polygons)
{
  double area = 0.0;
  int j = polygons.points.size() - 1;
  for (size_t i = 0; i < polygons.points.size(); ++i)
  {
    area += (polygons.points[j].x + polygons.points[i].x) * (polygons.points[j].y - polygons.points[i].y);
    j = i;
  }
  return std::abs(area) / 2.0;
}

int hohlova::countVertices(const Polygon& polygon)
{
  return polygon.points.size();
}

void hohlova::AREACommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using CommandFunction = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::map< std::string, CommandFunction > subcommand;
  {
    using namespace std::placeholders;
    subcommand["EVEN"] = std::bind(AREACommandEven, _1, _2);
    subcommand["ODD"] = std::bind(AREACommandOdd, _1, _2);
    subcommand["MEAN"] = std::bind(AREACommandMean, _1, _2);
  }
  std::string incommand;
  in >> incommand;
  try
  {
    subcommand.at(incommand)(polygons, out);
  }
  catch (const std::exception& e)
  {
    if (std::isdigit(incommand[0]))
    {
      unsigned long long numVertices = std::stoull(incommand);
      AREACommandNumVertices(polygons, numVertices, out);
    }
    else
      Error(out);
  }
}

void hohlova::AREACommandEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  double totalArea = 0.0;
  for (const auto& polygon : polygons)
  {
    if (countVertices(polygon) % 2 == 0)
    {
      totalArea += CalcArea(polygon);
    }
  }
  out << std::fixed << std::setprecision(1) << totalArea << "\n";
}

void hohlova::AREACommandOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  double totalArea = 0.0;
  for (const auto& polygon : polygons)
  {
    if (countVertices(polygon) % 2 != 0)
    {
      totalArea += CalcArea(polygon);
    }
  }
  out << std::fixed << std::setprecision(1) << totalArea << "\n";
}

void hohlova::AREACommandMean(const std::vector< Polygon >& polygons, std::ostream& out)
{
  double totalArea = 0.0;
  int count = 0;
  for (const auto& polygon : polygons)
  {
    totalArea += CalcArea(polygon);
    count++;
  }
  if (count > 0)
  {
    double meanArea = totalArea / count;
    out << std::fixed << std::setprecision(1) << meanArea << "\n";
  }
  else
  {
    Error(out);
  }
}

void hohlova::AREACommandNumVertices(const std::vector< Polygon >& polygons, unsigned long long numVertices, std::ostream& out)
{
  double totalArea = 0.0;
  if (numVertices < 3)
  {
    Error(out);
  }
  else
  {
    for (const auto& polygon : polygons)
    {
      if (countVertices(polygon) == numVertices)
      {
        totalArea += CalcArea(polygon);
      }
    }
    out << std::fixed << std::setprecision(1) << totalArea << "\n";
  }
}

void hohlova::MAXCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  using CommandFunction = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::map< std::string, CommandFunction > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(MAXCommandArea, _1, _2);
    subcommand["VERTEXES"] = std::bind(MAXCommandVertices, _1, _2);
  }
  std::string incommand;
  in >> incommand;
  try
  {
    subcommand.at(incommand)(polygons, out);
  }
  catch (const std::exception& e)
  {
    Error(out);
  }
}

void hohlova::MAXCommandArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  int count = 0;
  double maxValue = 0.0;
  for (const auto& polygon : polygons)
  {
    count++;
    double area = CalcArea(polygon);
    if (area > maxValue)
    {
      maxValue = area;
    }
  }
  if (count == 0)
    Error(out);
  else
    out << std::fixed << std::setprecision(1) << maxValue << "\n";
}

void hohlova::MAXCommandVertices(const std::vector< Polygon >& polygons, std::ostream& out)
{
  int maxVertices = 0;
  int count = 0;
  for (const auto& polygon : polygons)
  {
    count++;
    int vertices = countVertices(polygon);
    if (vertices > maxVertices)
    {
      maxVertices = vertices;
    }
  }
  if (count == 0)
    Error(out);
  else
    out << maxVertices << "\n";
}

void hohlova::MINCommandMenu(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using CommandFunction = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::map< std::string, CommandFunction > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(MINCommandArea, _1, _2);
    subcommand["VERTEXES"] = std::bind(MINCommandVertices, _1, _2);
  }
  std::string incommand;
  in >> incommand;
  try
  {
    subcommand.at(incommand)(polygons, out);
  }
  catch (const std::exception& e)
  {
    Error(out);
  }
}

void hohlova::MINCommandArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  double minValue = std::numeric_limits< double >::max();
  for (const auto& polygon : polygons)
  {
    double area = CalcArea(polygon);
    if (area < minValue)
    {
      minValue = area;
    }
  }

  out << std::fixed << std::setprecision(1) << minValue << "\n";
}

void hohlova::MINCommandVertices(const std::vector<Polygon>& polygons, std::ostream& out)
{
  int minVertices = std::numeric_limits< int >::max();
  for (const auto& polygon : polygons)
  {
    int vertices = countVertices(polygon);
    if (vertices < minVertices)
    {
      minVertices = vertices;
    }
  }
  out << minVertices << "\n";
}

void hohlova::COUNTCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  using CommandFunction = std::function<void(const std::vector<Polygon>&, std::ostream&)>;
  std::map<std::string, CommandFunction> subcommand;
  {
    using namespace std::placeholders;
    subcommand["EVEN"] = std::bind(COUNTCommandEven, _1, _2);
    subcommand["ODD"] = std::bind(COUNTCommandOdd, _1, _2);
  }
  std::string incommand;
  in >> incommand;
  try
  {
    subcommand.at(incommand)(polygons, out);
  }
  catch (const std::exception& e)
  {
    if (std::isdigit(incommand[0]))
    {
      unsigned long long numVertices = std::stoull(incommand);
      COUNTCommandNumVertices(polygons, numVertices, out);
    }
    else
      Error(out);
  }
}

void hohlova::COUNTCommandOdd(const std::vector<Polygon>& polygons, std::ostream& out)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    if (countVertices(polygon) % 2 != 0)
    {
      count++;
    }
  }
  out << count << "\n";
}

void hohlova::COUNTCommandEven(const std::vector<Polygon>& polygons, std::ostream& out)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    if (countVertices(polygon) % 2 == 0)
    {
      count++;
    }
  }
  out << count << "\n";
}

void hohlova::COUNTCommandNumVertices(const std::vector<Polygon>& polygons, unsigned long long numVertices, std::ostream& out)
{
  int count = 0;
  if (numVertices < 3)
  {
    Error(out);
    return;
  }
  for (const auto& polygon : polygons)
  {
    if (countVertices(polygon) == numVertices)
    {
      count++;
    }
  }
  out << count << "\n";
}

void hohlova::PERMSCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  Polygon polyg;
  in >> polyg;
  if (in.fail())
  {
    in.clear();
  }
  else
  {
    PERMScount(polyg, polygons, out);
    int count = PERMScount(polyg, polygons, out);
    out << count << "\n";
  }
}

int hohlova::PERMScount(const Polygon& polyg, const std::vector<Polygon>& polygons, std::ostream& out)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    if (polygon.points.size() != polyg.points.size())
    {
      continue;
    }
    bool isPermutation = true;
    std::vector< bool > used(polyg.points.size(), false);
    for (const auto& point : polygon.points)
    {
      isPermutation = false;
      for (size_t i = 0; i < polyg.points.size(); ++i)
      {
        if (!used[i] && ((point.x == polyg.points[i].x && point.y == polyg.points[i].y) || (point.x == polyg.points[i].y && point.y == polyg.points[i].x)))
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
void hohlova::MAXSEQCommandMenu(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (in.fail())
  {
    Error(out);
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
  }
  int max_seq = 0;
  int current_seq = 0;
  for (const auto& polyg : polygons)
  {
    if (polyg == polygon)
    {
      current_seq++;
      max_seq = std::max(max_seq, current_seq);
    }
    else
    {
      current_seq = 0;
    }
  }
  out << max_seq << "\n";
}

void hohlova::RIGHTSHAPESCommandMenu(const std::vector<Polygon>& polygons, std::ostream& out)
{
  int count = countRightShapes(polygons);
  out << count << "\n";
}

int hohlova::countRightShapes(const std::vector<Polygon>& polygons)
{
  int count = 0;
  for (const auto& polygon : polygons)
  {
    bool isRightShape = false;
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
        isRightShape = true;
        break;
      }
    }
    if (isRightShape)
    {
      count++;
    }
  }
  return count;
}
