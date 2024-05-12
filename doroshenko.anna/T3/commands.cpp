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
  //cmdsArea["ODD"] = std::bind(doroshenko::oddArea, _1, _2);
  //cmdsArea["MEAN"] = std::bind(doroshenko::meanArea, _1, _2);
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
        throw std::invalid_argument("Wrong input\n");
      }
      else
      {
        //vertexArea(num, polygons, output);
      }
    }
    else
    {
      throw std::invalid_argument("Wrong input\n");
    }
  }
}

void doroshenko::evenArea(const std::vector< Polygon >& polygons, std::ostream& output)
{
  std::vector< Polygon > evenPolygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(evenPolygons), [](const Polygon& pol) { return pol.points.size() % 2 == 0; });
  double sumArea = std::accumulate(evenPolygons.begin(), evenPolygons.end(), 0.0, plusArea);
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
  return 0.5 * std::abs(polygon.points[i].x * polygon.points[i + 1].y - polygon.points[i].y * polygon.points[i + 1].x) +
    calculatePolygonAreaRec(polygon, i + 1);
}

double doroshenko::calculatePolygonArea(const Polygon& polygon)
{
  return calculatePolygonAreaRec(polygon);
}
