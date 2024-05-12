#include "commands.hpp"
#include <map>
#include <functional>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <numeric>
#include "polygon.hpp"

void doroshenko::cmdArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsArea;
  cmdsArea["EVEN"] = std::bind(doroshenko::evenArea, _1, _2);
  cmdsArea["ODD"] = std::bind(doroshenko::oddArea, _1, _2);
  cmdsArea["MEAN"] = std::bind(doroshenko::meanArea, _1, _2);
  std::string areaType;
  input >> areaType;
  try
  {
    cmdsArea.at(areaType)(polygons, output);
  }
  catch (const std::out_of_range& e)
  {
    if (std::isdigit(areaType[0]))
    {
      size_t num = std::stoull(areaType);
      if (num < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>\n");
      }
      else
      {
        vertexArea(num, polygons, output);
      }
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
}

void doroshenko::evenArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(evenPolygons),
    [](const Polygon& pol) { return pol.points.size() % 2 == 0; }
  );
  double sumArea = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, plusArea);
  output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

void doroshenko::oddArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< Polygon > oddPolygons;
  std::copy_if
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(oddPolygons),
    [](const Polygon& pol) { return pol.points.size() % 2 != 0; }
  );
  double sumArea = std::accumulate(oddPolygons.begin(), oddPolygons.end(), 0.0, plusArea);
  output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

void doroshenko::meanArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, plusArea) / polygons.size();
  output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

void doroshenko::vertexArea(size_t num, const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< Polygon > needPolygons;
  std::copy_if
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(needPolygons),
    [num](const Polygon& pol) { return pol.points.size() == num; }
  );
  double sumArea = std::accumulate(needPolygons.begin(), needPolygons.end(), 0.0, plusArea);
  output << std::fixed << std::setprecision(1) << sumArea << "\n";
}

double doroshenko::plusArea(double sum, const Polygon& polygon)
{
  sum += calculatePolygonArea(polygon);
  return sum;
}

double doroshenko::calculatePolygonAreaRec(const Polygon& polygon, size_t i)
{
  if (i >= polygon.points.size() - 1)
  {
    return 0.0;
  }
  return 0.5 * std::abs(polygon.points[i].x * polygon.points[i + 1].y
    - polygon.points[i].y * polygon.points[i + 1].x) + calculatePolygonAreaRec(polygon, i + 1);
}

double doroshenko::calculatePolygonArea(const Polygon& polygon)
{
  return calculatePolygonAreaRec(polygon);
}

void doroshenko::cmdMax(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMax;
  cmdsMax["AREA"] = std::bind(doroshenko::findMaxArea, _1, _2);
  cmdsMax["VERTEXES"] = std::bind(doroshenko::findMaxVertexes, _1, _2);
  std::string maxType;
  input >> maxType;
  try
  {
    cmdsMax.at(maxType)(polygons, output);
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("<INVALID COMMAND\n");
  }
}

void doroshenko::findMaxArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< double > areasOfPolygons;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), calculatePolygonArea);
  std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
  output << std::fixed << std::setprecision(1) << areasOfPolygons[areasOfPolygons.size() - 1] << "\n";
}

void doroshenko::findMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< size_t > vertexes;
  std::transform
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexes),
    [](const Polygon& pol) { return pol.points.size(); }
  );
  std::sort(vertexes.begin(), vertexes.end());
  output << vertexes[vertexes.size() - 1] << "\n";
}

void doroshenko::cmdMin(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMin;
  cmdsMin["AREA"] = std::bind(doroshenko::findMinArea, _1, _2);
  cmdsMin["VERTEXES"] = std::bind(doroshenko::findMinVertexes, _1, _2);
  std::string minType;
  input >> minType;
  try
  {
    cmdsMin.at(minType)(polygons, output);
  }
  catch (const std::out_of_range& e)
  {
    throw std::invalid_argument("<INVALID COMMAND\n");
  }
}

void doroshenko::findMinArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< double > areasOfPolygons;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areasOfPolygons), calculatePolygonArea);
  std::sort(areasOfPolygons.begin(), areasOfPolygons.end());
  output << std::fixed << std::setprecision(1) << areasOfPolygons[0];
}

void doroshenko::findMinVertexes(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< size_t > vertexes;
  std::transform
  (
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexes),
    [](const Polygon& pol) { return pol.points.size(); }
  );
  std::sort(vertexes.begin(), vertexes.end());
  output << vertexes[0];
}

void doroshenko::cmdCount(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsCount;
  cmdsCount["EVEN"] = std::bind(doroshenko::countEven, _1, _2);
  cmdsCount["ODD"] = std::bind(doroshenko::countOdd, _1, _2);
  std::string countType;
  input >> countType;
  try
  {
    cmdsCount.at(countType)(polygons, output);
  }
  catch (const std::out_of_range& e)
  {
    if (std::isdigit(countType[0]))
    {
      size_t num = std::stoull(countType);
      if (num < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>\n");
      }
      else
      {
        vertexCount(num, polygons, output);
      }
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
}

void doroshenko::countEven(const std::vector< Polygon >& polygons, std::ostream& output)
{
  size_t result = std::count_if
  (
    polygons.begin(),
    polygons.end(),
    [](const Polygon& pol) { return pol.points.size() % 2 == 0; }
  );
  output << result << "\n";
}

void doroshenko::countOdd(const std::vector< Polygon >& polygons, std::ostream& output)
{
  size_t result = std::count_if
  (
    polygons.begin(),
    polygons.end(),
    [](const Polygon& pol) { return pol.points.size() % 2 != 0; }
  );
  output << result << "\n";
}

void doroshenko::vertexCount(size_t num, const std::vector< Polygon >& polygons, std::ostream& output)
{
  size_t result = std::count_if
  (
    polygons.begin(),
    polygons.end(),
    [num](const Polygon& pol) { return pol.points.size() == num; }
  );
  output << result << "\n";
}
