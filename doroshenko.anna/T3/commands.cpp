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
  auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
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
        warningInvCom(output);
      }
      else
      {
        vertexArea(num, polygons, output);
      }
    }
    else
    {
      warningInvCom(output);
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
  auto warningInvCom = std::bind(warning, std::placeholders::_1, "<INVALID COMMAND>\n");
  if(polygons.empty())
  {
    warningInvCom(output);
  }
  else
  {
    double sumArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, plusArea) / polygons.size();
    output << std::fixed << std::setprecision(1) << sumArea << "\n";
  }
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

double doroshenko::calculatePolygonAreaRec(const Polygon& polygon, size_t i, double area)
{
  const size_t numPoints = polygon.points.size();
  if (i >= numPoints)
  {
    return area;
  }
  const Point& p1 = polygon.points[i];
  const Point& p2 = polygon.points[(i + 1) % numPoints];
  return calculatePolygonAreaRec(polygon, i + 1, area + (p1.x * p2.y - p2.x * p1.y));
}

double doroshenko::calculatePolygonArea(const Polygon& polygon)
{
  return 0.5 * std::abs(calculatePolygonAreaRec(polygon, 0, 0.0));
}

void doroshenko::cmdMax(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > > cmdsMax;
  cmdsMax["AREA"] = std::bind(doroshenko::findMaxArea, _1, _2);
  cmdsMax["VERTEXES"] = std::bind(doroshenko::findMaxVertexes, _1, _2);
  auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
  std::string maxType;
  input >> maxType;
  try
  {
    if(polygons.empty())
    {
      warningInvCom(output);
    }
    else
    {
      cmdsMax.at(maxType)(polygons, output);
    }
  }
  catch (const std::out_of_range& e)
  {
    warningInvCom(output);
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
  auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
  std::string minType;
  input >> minType;
  try
  {
    if(polygons.empty())
    {
      warningInvCom(output);
    }
    cmdsMin.at(minType)(polygons, output);
  }
  catch (const std::out_of_range& e)
  {
    warningInvCom(output);
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
  auto warningInvCom = std::bind(warning, _1, "<INVALID COMMAND>\n");
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
        warningInvCom(output);
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

void doroshenko::cmdRmecho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  size_t currentSize = polygons.size();
  if (currentSize == 0)
  {
    output << currentSize << "\n";
    return;
  }

  Polygon toRemove;
  input >> toRemove;

  bool lastRemoved = false;
  auto it = std::remove_if
  (
    polygons.begin(),
    polygons.end(),
    [&toRemove, &lastRemoved](const Polygon& p)
    {
      if (p == toRemove && lastRemoved)
      {
        return true;
      }
      lastRemoved = (p == toRemove);
      return false;
     }
  );
  polygons.erase(it, polygons.end());
  size_t removedCount = currentSize - polygons.size();
  output << removedCount << '\n';
}

bool doroshenko::arePolygonsCompatible(Polygon& a, Polygon& b)
{
  if (a.points.size() != b.points.size())
  {
    return false;
  }
  Polygon sortedA = a;
  std::transform(sortedA.points.begin(), sortedA.points.end(), a.points.begin(), [](Point& p){
    Point point;
    point.x = std::abs(p.x);
    point.y = std::abs(p.y);
    return point;
  });
  std::sort
  (
    sortedA.points.begin(),
    sortedA.points.end(),
    [](Point& fP, Point& sP){return fP.x == sP.x ? fP.y < sP.y : fP.x < sP.x;}
  );
  Polygon sortedB = b;
  std::transform(sortedB.points.begin(), sortedB.points.end(), b.points.begin(), [](Point& p){
    Point point;
    point.x = std::abs(p.x);
    point.y = std::abs(p.y);
    return point;
  });
  std::sort
  (
    sortedB.points.begin(),
    sortedB.points.end(),
    [](Point& fP, Point& sP){return fP.x != sP.x ? fP.x < sP.x : fP.y < sP.y;}
  );
  Point diff;
  diff.x = sortedA.points[0].x - sortedB.points[0].x;
  diff.y = sortedA.points[0].y - sortedB.points[0].y;
  return std::equal
  (
    sortedA.points.begin(),
    sortedA.points.end(),
    sortedB.points.begin(),
    [diff](Point& fP, Point& sP)
    {
      return fP.x - sP.x == diff.x && fP.y - sP.y == diff.y;
    }
  );
}

void doroshenko::cmdSame(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  auto warningInvCom = std::bind(warning, std::placeholders::_1, "<INVALID COMMAND>\n");
  Polygon target;
  input >> target;
  char c = input.peek();
  if(c != '\n' || input.fail())
  {
    warningInvCom(output);
    throw std::invalid_argument("");
  }
  else
  {
    size_t compatibleCount = std::count_if
    (
      polygons.begin(),
      polygons.end(),
      [&target](Polygon& polygon) { return arePolygonsCompatible(polygon, target); }
    );
    output << compatibleCount << '\n';
  }
}

void doroshenko::warning(std::ostream& output, const std::string& mes)
{
  output << mes;
}
