#include "commands.hpp"
#include <functional>
#include <limits>
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

double zheleznyakov::areaAccumulator(double currentSum, const Polygon & poly)
{
  return currentSum + calculatePolygonArea(poly, 0, 0.0);
}

double zheleznyakov::oddAreaAccumulator(double currentSum, const Polygon & poly)
{
  return currentSum + (poly.points.size() % 2 != 0 ? calculatePolygonArea(poly, 0, 0.0) : 0);
}

double zheleznyakov::evenAreaAccumulator(double currentSum, const Polygon & poly)
{
  return currentSum + (poly.points.size() % 2 == 0 ? calculatePolygonArea(poly, 0, 0.0) : 0);
}

double zheleznyakov::vertexAreaAccumulator(double currentSum, const Polygon & poly, size_t vertexes)
{
  return currentSum + (poly.points.size() == vertexes ? calculatePolygonArea(poly, 0, 0.0) : 0);
}

double zheleznyakov::processAreaEven(const std::vector< Polygon > & polys)
{
  return std::accumulate(polys.begin(), polys.end(), 0, evenAreaAccumulator);
}

double zheleznyakov::processAreaOdd(const std::vector< Polygon > & polys)
{
  return std::accumulate(polys.begin(), polys.end(), 0, oddAreaAccumulator);
}

double zheleznyakov::processAreaMean(const std::vector< Polygon > & polys)
{
  return std::accumulate(polys.begin(), polys.end(), 0, areaAccumulator) / polys.size();
}

double zheleznyakov::processAreaVertexes(const std::vector< Polygon > & polys, size_t vertexes)
{
  using namespace std::placeholders;
  return std::accumulate(polys.begin(), polys.end(), 0, std::bind(vertexAreaAccumulator, _1, _2, vertexes));
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

double zheleznyakov::processMaxArea(const std::vector< Polygon > & polys)
{
  using namespace std::placeholders;
  std::vector < const double > areas;
  std::transform(polys.begin(), polys.end(), std::back_inserter(areas), std::bind(calculatePolygonArea, _1, 0, 0.0));
  return * std::max_element(areas.begin(), areas.end());
}

size_t zheleznyakov::processMaxVertex(const std::vector< Polygon > & polys)
{
  using namespace std::placeholders;
  std::vector < const double > vertex;
  std::transform(polys.begin(), polys.end(), std::back_inserter(vertex), [](const Polygon & p){
    return p.points.size();
  });
  return * std::max_element(vertex.begin(), vertex.end());
}
