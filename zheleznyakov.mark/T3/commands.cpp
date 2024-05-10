#include "commands.hpp"
#include <functional>
#include <limits>
#include <algorithm>
#include <iostream>
#include <numeric>

std::ostream & zheleznyakov::commands::area(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string subCmd = "";
  in >> subCmd;
  out << std::fixed << std::setprecision(1);
  if (subCmd == "EVEN")
  {
    return out << processAreaEven(polygons) << '\n';
  }
  else if (subCmd == "ODD")
  {
    return out << processAreaOdd(polygons) << '\n';
  }
  else if (subCmd == "MEAN")
  {
    return out << processAreaMean(polygons) << '\n';
  }
  size_t vertexes = std::stoll(subCmd);
  return out << processAreaVertexes(polygons, vertexes) << '\n';
}

double zheleznyakov::areaAccumulator(double currentSum, const Polygon & polygon)
{
  return currentSum + calculatePolygonArea(polygon, 0, 0.0);
}

double zheleznyakov::oddAreaAccumulator(double currentSum, const Polygon & polygon)
{
  return currentSum + (polygon.points.size() % 2 != 0 ? calculatePolygonArea(polygon, 0, 0.0) : 0);
}

double zheleznyakov::evenAreaAccumulator(double currentSum, const Polygon & polygon)
{
  return currentSum + (polygon.points.size() % 2 == 0 ? calculatePolygonArea(polygon, 0, 0.0) : 0);
}

double zheleznyakov::vertexAreaAccumulator(double currentSum, const Polygon & polygon, size_t vertexes)
{
  return currentSum + (polygon.points.size() == vertexes ? calculatePolygonArea(polygon, 0, 0.0) : 0);
}

double zheleznyakov::processAreaEven(const std::vector< Polygon > & polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0, evenAreaAccumulator);
}

double zheleznyakov::processAreaOdd(const std::vector< Polygon > & polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0, oddAreaAccumulator);
}

double zheleznyakov::processAreaMean(const std::vector< Polygon > & polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0, areaAccumulator) / polygons.size();
}

double zheleznyakov::processAreaVertexes(const std::vector< Polygon > & polygons, size_t vertexes)
{
  using namespace std::placeholders;
  return std::accumulate(polygons.begin(), polygons.end(), 0, std::bind(vertexAreaAccumulator, _1, _2, vertexes));
}

std::ostream & zheleznyakov::commands::max(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string subCmd = "";
  in >> subCmd;
  out << std::fixed << std::setprecision(1);
  if (subCmd == "AREA")
  {
    return out << processMaxArea(polygons) << '\n';
  }
  else if (subCmd == "VERTEXES")
  {
    return out << processMaxVertex(polygons) << '\n';
  }
  return out;
}

double zheleznyakov::processMaxArea(const std::vector< Polygon > & polygons)
{
  using namespace std::placeholders;
  std::vector < double > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), std::bind(calculatePolygonArea, _1, 0, 0.0));
  return * std::max_element(areas.begin(), areas.end());
}

size_t zheleznyakov::processMaxVertex(const std::vector< Polygon > & polygons)
{
  using namespace std::placeholders;
  std::vector < double > vertex;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertex), [](const Polygon & p){
    return p.points.size();
  });
  return * std::max_element(vertex.begin(), vertex.end());
}

std::ostream & zheleznyakov::commands::min(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string subCmd = "";
  in >> subCmd;
  out << std::fixed << std::setprecision(1);
  if (subCmd == "AREA")
  {
    return out << processMinArea(polygons) << '\n';
  }
  else if (subCmd == "VERTEXES")
  {
    return out << processMinVertex(polygons) << '\n';
  }
  return out;
}


double zheleznyakov::processMinArea(const std::vector< Polygon > & polygons)
{
  using namespace std::placeholders;
  std::vector < double > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), std::bind(calculatePolygonArea, _1, 0, 0.0));
  return * std::min_element(areas.begin(), areas.end());
}

size_t zheleznyakov::processMinVertex(const std::vector< Polygon > & polygons)
{
  using namespace std::placeholders;
  std::vector < double > vertex;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(vertex), [](const Polygon & p){
    return p.points.size();
  });
  return * std::min_element(vertex.begin(), vertex.end());
}

std::ostream & zheleznyakov::commands::count(const std::vector< Polygon > & polygons, std::istream & in, std::ostream & out)
{
  std::string subCmd = "";
  in >> subCmd;
  out << std::fixed << std::setprecision(1);
  if (subCmd == "EVEN")
  {
    return out << processCountEven(polygons) << '\n';
  }
  else if (subCmd == "ODD")
  {
    return out << processCountOdd(polygons) << '\n';
  }
  else
  {
    size_t vertexes = std::stoll(subCmd);
    return out << processCountVertex(polygons, vertexes) << '\n';
  }
}

size_t zheleznyakov::processCountEven(const std::vector< Polygon > & polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), polygonIsVertexesEven);
}

size_t zheleznyakov::processCountOdd(const std::vector< Polygon > & polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), polygonIsVertexesOdd);
}

size_t zheleznyakov::processCountVertex(const std::vector< Polygon > & polygons, const size_t vertexes)
{
  using namespace std::placeholders;
  return std::count_if(polygons.begin(), polygons.end(), std::bind(polygonIsVertexesEquals, _1, vertexes));
}

bool zheleznyakov::polygonIsVertexesOdd(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zheleznyakov::polygonIsVertexesEven(const Polygon & polygon)
{
  return polygon.points.size() % 2 != 0;
}

bool zheleznyakov::polygonIsVertexesEquals(const Polygon & polygon, const size_t vertexes)
{
  return polygon.points.size() == vertexes;
}
