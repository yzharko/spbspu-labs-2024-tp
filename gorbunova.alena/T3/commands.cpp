#include <map>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
#include <functional>
#include "operations.hpp"

using namespace std::placeholders;

void gorbunova::cmdArea(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > &polygons, std::ostream &out) > > areaCmds;
  areaCmds["EVEN"] = [](const std::vector< Polygon > &polygons, std::ostream &out)
  { areaEven(polygons, out); };
  areaCmds["ODD"] = [](const std::vector< Polygon > &polygons, std::ostream &out)
  { areaOdd(polygons, out); };
  areaCmds["MEAN"] = [](const std::vector< Polygon > &polygons, std::ostream &out)
  { areaMean(polygons, out); };
  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string type;
  is >> type;
  try
  {
    areaCmds.at(type)(polygons, out);
  }
  catch (const std::out_of_range &e)
  {
    if (std::isdigit(type[0]) && std::stoull(type) > 2)
    {
      areaNumOfVertexes(std::stoull(type), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void gorbunova::cmdMax(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > &polygons, std::ostream &out) > > maxCmds;
  maxCmds["AREA"] = maxArea;
  maxCmds["VERTEXES"] = maxVertexes;
  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string type;
  is >> type;
  try
  {
    if (std::isdigit(type[0]) && std::stoull(type) > 2)
    {
      countNumOfVertexes(std::stoull(type), polygons, out);
    }
    else
    {
      maxCmds.at(type)(polygons, out);
    }
  }
  catch (const std::out_of_range &e)
  {
    outInvalid(out);
  }
}

void gorbunova::cmdMin(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > &polygons, std::ostream &out) > > minCmds;
  minCmds["AREA"] = minArea;
  minCmds["VERTEXES"] = minVertexes;
  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string type;
  is >> type;
  try
  {
    minCmds.at(type)(polygons, out);
  }
  catch (const std::out_of_range &e)
  {
    outInvalid(out);
  }
}

void gorbunova::cmdCount(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  std::map< std::string, std::function< void(const std::vector< Polygon > &polygons, std::ostream &out) > > countCmds;
  countCmds["EVEN"] = countEven;
  countCmds["ODD"] = countOdd;
  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::string type;
  is >> type;
  try
  {
    countCmds.at(type)(polygons, out);
  }
  catch (const std::out_of_range &e)
  {
    if (std::isdigit(type[0]) && std::stoull(type) > 2)
    {
      countNumOfVertexes(std::stoull(type), polygons, out);
    }
    else
    {
      outInvalid(out);
    }
  }
}

void gorbunova::cmdPerms(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  Polygon givenPolygon;
  is >> givenPolygon;
  size_t givenPolygonVertexes = givenPolygon.points.size();
  auto outInvalid = std::bind(printMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  std::vector< Polygon > allVertexes;
  std::copy_if(
    polygons.begin(),
    polygons.end(),
    std::back_inserter(allVertexes),
    [givenPolygonVertexes](const Polygon &polygon)
    {
      return polygon.points.size() == givenPolygonVertexes;
    });
  if (allVertexes.empty())
  {
    outInvalid(out);
  }
  else
  {
    auto comparePolygon = std::bind(checkPerms, givenPolygon, _1);
    size_t count = std::count_if(polygons.begin(), polygons.end(), comparePolygon);
    out << count << '\n';
  }
}

void gorbunova::cmdInframe(const std::vector< Polygon > &polygons, std::ostream &out, std::istream &is)
{
  Polygon queryPolygon;
  is >> queryPolygon;
  Point topLeft = {std::numeric_limits< int >::max(), std::numeric_limits< int >::min()};
  Point bottomRight = {std::numeric_limits< int >::min(), std::numeric_limits< int >::max()};
  std::for_each(polygons.begin(), polygons.end(), [&](const Polygon &polygon)
    { std::for_each(polygon.points.begin(), polygon.points.end(), [&](const Point &point)
      { updateFrame(point, topLeft, bottomRight); }); });
  bool isInFrame = std::all_of(queryPolygon.points.begin(), queryPolygon.points.end(), [&](const Point &point)
    { return pointInFrame(point, topLeft, bottomRight); });
  out << (isInFrame ? "<TRUE>" : "<FALSE>") << '\n';
}

void gorbunova::printMessage(std::ostream &out, const std::string &message)
{
  out << message;
}
