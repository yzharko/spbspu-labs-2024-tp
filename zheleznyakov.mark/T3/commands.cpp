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
    if (polygons.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    return out << processAreaMean(polygons) << '\n';
  }
  size_t vertexes = std::stoll(subCmd);
  if (vertexes <= 2)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
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

double zheleznyakov::evenAreaAccumulator(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0 ? calculatePolygonArea(polygon, 0, 0.0) : 0;
}

double zheleznyakov::vertexAreaAccumulator(double currentSum, const Polygon & polygon, size_t vertexes)
{
  return currentSum + (polygon.points.size() == vertexes ? calculatePolygonArea(polygon, 0, 0.0) : 0);
}

double zheleznyakov::processAreaEven(const std::vector< Polygon > & polygons)
{
  std::vector< double > areas;
  std::transform(polygons.begin(), polygons.end(), std::back_inserter(areas), evenAreaAccumulator);
  return std::accumulate(areas.begin(), areas.end(), 0);
}

double zheleznyakov::processAreaOdd(const std::vector< Polygon > & polygons)
{
  return std::accumulate(polygons.begin(), polygons.end(), 0, oddAreaAccumulator);
}

double zheleznyakov::processAreaMean(const std::vector< Polygon > & polygons)
{
  return static_cast< double >(std::accumulate(polygons.begin(), polygons.end(), 0, areaAccumulator)) / polygons.size();
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
  if (polygons.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
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
    if (vertexes <= 2)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
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
  return polygon.points.size() % 2 != 0;
}

bool zheleznyakov::polygonIsVertexesEven(const Polygon & polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool zheleznyakov::polygonIsVertexesEquals(const Polygon & polygon, const size_t vertexes)
{
  return polygon.points.size() == vertexes;
}

std::ostream & zheleznyakov::commands::maxseq(const std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  Polygon target;
  in >> target;
  size_t v = processMaxseq(polygon, target);
  return out << v << '\n';
}

size_t zheleznyakov::processMaxseq(const std::vector<Polygon>& polygons, const Polygon& target)
{
  if (polygons.size() <= 2)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::vector< size_t > results;
  {
    using namespace std::placeholders;
    std::transform(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(results),
      std::bind(maxseqTransformHelper, _1, target)
    );
  }
  return *std::max_element(results.begin(), results.end());
}

size_t zheleznyakov::maxseqTransformHelper(const Polygon& polygon, const Polygon& target)
{
  static size_t currentSeq = 0;
  if (polygon == target)
  {
    currentSeq++;
    return currentSeq;
  }
  else
  {
    currentSeq = 0;
    return currentSeq;
  }
}

std::ostream & zheleznyakov::commands::same(const std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  Polygon target;
  in >> target;
  if (!in)
  {
    throw std::logic_error("");
  }
  size_t v = processSame(polygon, target);
  return out << v << '\n';
}

size_t zheleznyakov::processSame(const std::vector<Polygon>& polygons, const Polygon& target)
{
  using namespace std::placeholders;
  return std::count_if(polygons.begin(), polygons.end(), std::bind(sameCountIfHelper, _1, target));
}

bool zheleznyakov::sameCountIfHelper(const Polygon& current, const Polygon& target)
{
  if (current.points.size() != target.points.size())
  {
    return false;
  }
  const Point movement = diffVector(current.points.at(0), target.points.at(0));
  std::vector< bool > results;
  {
    using namespace std::placeholders;
    std::transform(
      target.points.begin(),
      target.points.end(),
      std::back_inserter(results),
      std::bind(hasLayeredPoints, current, _1, movement)
    );
  };
  return std::all_of(results.begin(), results.end(), [](bool r){ return r; });
}

zheleznyakov::Point zheleznyakov::diffVector(const Point & p1, const Point & p2)
{
  return Point{p2.x - p1.x, p2.y - p1.y};
}

bool zheleznyakov::hasLayeredPoints(const Polygon & p1, const Point & p2, const Point & movement)
{
  using namespace std::placeholders;
  bool haveAllPointsLayering = std::any_of(p1.points.begin(), p1.points.end(), std::bind(arePointsLayering, _1, p2, movement));
  return haveAllPointsLayering;
}

bool zheleznyakov::arePointsLayering(const Point & p1, const Point & p2, const Point & movement)
{
  return Point{p1.x + movement.x, p1.y + movement.y} == p2;
}

void zheleznyakov::outMessage(std::ostream & out, std::string msg)
{
  iofmtguard fmtguard(out);
  out << msg;
}
