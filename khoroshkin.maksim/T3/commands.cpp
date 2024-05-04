#include "commands.hpp"
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std::placeholders;

void khoroshkin::cmdArea(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > & polygons, std::ostream & out) > > areaCmds;
  areaCmds["EVEN"] = processEven;
  areaCmds["ODD"] = processOdd;
  areaCmds["MEAN"] = processMean;
  std::string type;
  is >> type;
  try
  {
    areaCmds.at(type)(polygons, out);
  }
  catch(const std::out_of_range & e)
  {
    if (std::isdigit(type[0]))
    {
      processAreaNum(std::stoull(type), polygons, out);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
  }
}

void khoroshkin::processEven(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< Polygon > onlyEvenPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyEvenPolygons),
    [](const Polygon & polygon){ return !(polygon.points.size() % 2); }
  );
  double sum = sumAllAreas(onlyEvenPolygons);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void khoroshkin::processOdd(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< Polygon > onlyOddPolygons;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(onlyOddPolygons),
    [](const Polygon & polygon){ return polygon.points.size() % 2; }
  );
  double sum = sumAllAreas(onlyOddPolygons);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

void khoroshkin::processMean(const std::vector< Polygon > & polygons, std::ostream & out)
{
  double sum = sumAllAreas(polygons);
  out << std::setprecision(1) << std::fixed << sum / polygons.size() << '\n';
}

void khoroshkin::processAreaNum(size_t vertexes, const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< Polygon > polygonsWithNVertexes;
  auto OnlyNVertexes = std::bind(std::equal_to< size_t >{}, vertexes, _1);
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [OnlyNVertexes](const Polygon & polygon){ return OnlyNVertexes(polygon.points.size()); }
  );

  double sum = sumAllAreas(polygonsWithNVertexes);
  out << std::setprecision(1) << std::fixed << sum << '\n';
}

double khoroshkin::sumAllAreas(const std::vector< Polygon > & polygons)
{
  std::vector< double > AreasOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon & polygon){ return getArea(polygon); }
  );

  double sumOfAreas = std::accumulate(
    AreasOfPolygons.begin(),
    AreasOfPolygons.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2)
  );
  return sumOfAreas;
}

double khoroshkin::getArea(const Polygon & polygon)
{
  std::vector< double > sumOfCoords;
  std::transform(
    polygon.points.begin(),
    polygon.points.end() - 1,
    std::next(polygon.points.begin()),
    std::back_inserter(sumOfCoords),
    [](const Point & a, const Point & b){ return a.x * b.y; }
  );

  std::vector< double > diffOfCoords;
  std::transform(
    polygon.points.begin(),
    polygon.points.end() - 1,
    std::next(polygon.points.begin()),
    std::back_inserter(diffOfCoords),
    [](const Point & a, const Point & b){ return a.y * b.x; }
  );

  double sum = std::accumulate(
    sumOfCoords.begin(),
    sumOfCoords.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2)
  );
  double diff = std::accumulate(
    diffOfCoords.begin(),
    diffOfCoords.end(),
    0,
    std::bind(std::plus< double >{}, _1, _2)
  );
  return 0.5 * std::abs(sum - diff);
}

void khoroshkin::cmdMax(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > & polygons, std::ostream & out) > > maxCmds;
  maxCmds["AREA"] = processMaxArea;
  maxCmds["VERTEXES"] = processMaxVertexes;
  std::string type;
  is >> type;
  try
  {
    maxCmds.at(type)(polygons, out);
  }
  catch(const std::out_of_range & e)
  {
    std::cerr << "<INVALID COMMAND>" << '\n';
  }
}

void khoroshkin::processMaxArea(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< double > AreasOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon & polygon){ return getArea(polygon); }
  );
  std::sort(AreasOfPolygons.begin(), AreasOfPolygons.end());
  out << std::setprecision(1) << std::fixed << AreasOfPolygons.back() << '\n';
}

void khoroshkin::processMaxVertexes(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< size_t > vertexesOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons),
    [](const Polygon & polygon){ return polygon.points.size(); }
  );
  std::sort(vertexesOfPolygons.begin(), vertexesOfPolygons.end());
  out << vertexesOfPolygons.back() << '\n';
}

void khoroshkin::cmdMin(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > & polygons, std::ostream & out) > > minCmds;
  minCmds["AREA"] = processMinArea;
  minCmds["VERTEXES"] = processMinVertexes;
  std::string type;
  is >> type;
  try
  {
    minCmds.at(type)(polygons, out);
  }
  catch(const std::out_of_range & e)
  {
    std::cerr << "<INVALID COMMAND>" << '\n';
  }
}

void khoroshkin::processMinArea(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< double > AreasOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(AreasOfPolygons),
    [](const Polygon & polygon){ return getArea(polygon); }
  );
  std::sort(AreasOfPolygons.begin(), AreasOfPolygons.end());
  out << std::setprecision(1) << std::fixed << AreasOfPolygons.front() << '\n';
}

void khoroshkin::processMinVertexes(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< size_t > vertexesOfPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(vertexesOfPolygons),
    [](const Polygon & polygon){ return polygon.points.size(); }
  );
  std::sort(vertexesOfPolygons.begin(), vertexesOfPolygons.end());
  out << vertexesOfPolygons.front() << '\n';
}

void khoroshkin::cmdCount(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > & polygons, std::ostream & out) > > countCmds;
  countCmds["EVEN"] = processCountEven;
  countCmds["ODD"] = processCountOdd;
  std::string type;
  is >> type;
  try
  {
    if (!polygons.empty())
    {
      countCmds.at(type)(polygons, out);
    }
    else
    {
      throw std::out_of_range("");
    }
  }
  catch(const std::out_of_range & e)
  {
    if (std::isdigit(type[0]) && !polygons.empty())
    {
      processCountVertexes(std::stoull(type), polygons, out);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
  }
}

void khoroshkin::processCountEven(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< size_t > evenPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(evenPolygons),
    [](const Polygon & polygon){ return !(polygon.points.size() % 2); }
  );
  size_t countEven = std::accumulate(
    evenPolygons.begin(),
    evenPolygons.end(),
    0,
    std::bind(std::plus< size_t >{}, _1, _2)
  );
  out << countEven << '\n';
}

void khoroshkin::processCountOdd(const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< size_t > oddPolygons;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(oddPolygons),
    [](const Polygon & polygon){ return polygon.points.size() % 2; }
  );
  size_t countOdd = std::accumulate(
    oddPolygons.begin(),
    oddPolygons.end(),
    0,
    std::bind(std::plus< size_t >{}, _1, _2)
  );
  out << countOdd << '\n';
}

void khoroshkin::processCountVertexes(size_t vertexes, const std::vector< Polygon > & polygons, std::ostream & out)
{
  std::vector< size_t > polygonsWithNVertexes;
  std::transform(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(polygonsWithNVertexes),
    [vertexes](const Polygon & polygon){ return polygon.points.size() == vertexes; }
  );
  size_t countWithNVertexes = std::accumulate(
    polygonsWithNVertexes.begin(),
    polygonsWithNVertexes.end(),
    0,
    std::bind(std::plus< size_t >{}, _1, _2)
  );
  out << countWithNVertexes << '\n';
}

void khoroshkin::cmdPerms(const std::vector< Polygon > & polygons, std::ostream & out, std::istream & is)
{
  Polygon givenPolygon;
  is >> givenPolygon;
  auto comparePolygon = std::bind(checkPerms, givenPolygon, _1);
  size_t count = std::count_if(polygons.begin(), polygons.end(), comparePolygon);
  out << count << '\n';
}

bool khoroshkin::checkPerms(const Polygon & lhs, const Polygon & rhs)
{
  if (lhs.points.size() != rhs.points.size())
  {
    return false;
  }
  auto isPointContains = std::bind(checkPoints, lhs, _1);
  long unsigned int countPointsIn = std::count_if(rhs.points.begin(), rhs.points.end(), isPointContains);
  return lhs.points.size() == countPointsIn;
}

bool khoroshkin::checkPoints(const Polygon & toCompare, const Point & point)
{
  return std::find_if(
    toCompare.points.begin(),
    toCompare.points.end(),
    [point](const Point & pointToCompare)
    {
      return (pointToCompare.x == point.x && pointToCompare.y == point.y) || (pointToCompare.x == point.y && pointToCompare.y == point.x);
    }) != toCompare.points.end();
}

void khoroshkin::cmdRightshapes(const std::vector< Polygon > & polygons, std::ostream & out)
{
  size_t count = std::count_if(polygons.begin(), polygons.end(), isAngleRight);
  out << count << '\n';
}

bool khoroshkin::isAngleRight(const Polygon & polygon)
{
  std::vector< Point > vectorFromPoints;
  std::transform(
    polygon.points.begin(),
    polygon.points.end(),
    std::next(polygon.points.begin()),
    std::back_inserter(vectorFromPoints),
    [](const Point & a, const Point & b){ return Point{ b.x - a.x, b.y - a.y }; }
  );
  std::vector< double > cosOfVectors;
  std::transform(
    vectorFromPoints.begin(),
    vectorFromPoints.end(),
    std::next(vectorFromPoints.begin()),
    std::back_inserter(cosOfVectors),
    [](const Point & a, const Point & b)
    {
      return (a.x * b.x + a.y * b.y) / (std::sqrt(a.x * a.x + a.y * a.y) * std::sqrt(b.x * b.x + b.y * b.y));
    }
  );
  return std::find_if(cosOfVectors.begin(), cosOfVectors.end(), [](const double & cos){ return cos == 0; }) != cosOfVectors.end();
}
